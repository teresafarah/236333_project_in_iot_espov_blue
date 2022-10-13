import 'dart:async';
import 'dart:convert';
import 'dart:ffi';
import 'dart:math';
import 'dart:typed_data';
import 'package:espov_at_home/global_vars.dart';
import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'global_vars.dart' as globals;

class ChatPage extends StatefulWidget {
  final BluetoothDevice? server;

  const ChatPage({required this.server});

  @override
  _ChatPage createState() => new _ChatPage();
}

class _Message {
  int whom;
  String text;

  _Message(this.whom, this.text);
}

class _ChatPage extends State<ChatPage> {
  // static final clientID = 0;
  BluetoothConnection? connection;

  List<_Message> messages = List<_Message>.empty(growable: true);
  String _messageBuffer = '';

  final TextEditingController textEditingController = TextEditingController();
  final ScrollController listScrollController = ScrollController();

  bool isConnecting = true;
  bool get isConnected => (connection?.isConnected ?? false);
  bool isSending = true;
  bool isDisconnecting = false;

  @override
  void initState() {
    super.initState();

    BluetoothConnection.toAddress(widget.server?.address).then((_connection) {
      print('Connected to the device');
      connection = _connection;
      setState(() {
        isConnecting = false;
        isDisconnecting = false;
        isSending = false;
      });

      connection!.input!.listen(_onDataReceived).onDone(() {
        // Example: Detect which side closed the connection
        // There should be `isDisconnecting` flag to show are we are (locally)
        // in middle of disconnecting process, should be set before calling
        // `dispose`, `finish` or `close`, which all causes to disconnect.
        // If we except the disconnection, `onDone` should be fired as result.
        // If we didn't except this (no flag set), it means closing by remote.
        if (isDisconnecting) {
          print('Disconnecting locally!');
        } else {
          print('Disconnected remotely!');
        }
        if (this.mounted) {
          setState(() {});
        }
      });
    }).catchError((error) {
      print('Cannot connect, exception occured');
      print(error);
    });
  }

  @override
  void dispose() {
    // Avoid memory leak (`setState` after dispose) and disconnect
    if (isConnected) {
      isDisconnecting = true;
      connection?.dispose();
      connection = null;
    }

    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    // final List<Row> list = messages.map((_message) {
    //   return Row(
    //     children: <Widget>[
    //       Container(
    //         child: Text(
    //             (text) {
    //               return text == '/shrug' ? '¯\\_(ツ)_/¯' : text;
    //             }(_message.text.trim()),
    //             style: TextStyle(color: Colors.white)),
    //         padding: EdgeInsets.all(12.0),
    //         margin: EdgeInsets.only(bottom: 8.0, left: 8.0, right: 8.0),
    //         width: 222.0,
    //         decoration: BoxDecoration(
    //             color:
    //                 _message.whom == clientID ? Colors.blueAccent : Colors.grey,
    //             borderRadius: BorderRadius.circular(7.0)),
    //       ),
    //     ],
    //     mainAxisAlignment: _message.whom == clientID
    //         ? MainAxisAlignment.end
    //         : MainAxisAlignment.start,
    //   );
    // }).toList();

    // final serverName = widget.server?.name ?? "Unknown";
    return Scaffold(
      // appBar: AppBar(
      //     title: (isConnecting
      //         ? Text('Connecting chat to ' + serverName + '...')
      //         : isConnected
      //             ? Text('Live chat with ' + serverName)
      //             : Text('Chat log with ' + serverName))),
      body: Center(
        child: Column(
          children: <Widget>[
            const Spacer(),
            Container(
                margin: const EdgeInsets.all(8.0),
                child: !isConnected
                    ? (const Text(
                        '   Connecting to device...   ',
                        style: TextStyle(
                          color: Colors.black,
                        ),
                      ))
                    : (isSending
                        ? (const Text(
                            '   Sending image...   ',
                            style: TextStyle(
                              color: Colors.black,
                            ),
                          ))
                        : (TextButton(
                            style: ButtonStyle(
                                backgroundColor:
                                    const MaterialStatePropertyAll<Color>(
                                        Color(0xff79d7dd)),
                                shape: MaterialStateProperty.all<
                                        RoundedRectangleBorder>(
                                    RoundedRectangleBorder(
                                  borderRadius: BorderRadius.circular(18.0),
                                ))),
                            onPressed: isConnected
                                ? () => {
                                      globals.list_of_int_images.forEach(
                                          (element) => _sendMessage(element))
                                    }
                                : null,
                            child: const Text(
                              '   Send image!   ',
                              style: TextStyle(
                                color: Color(0xFFFFFFFF),
                              ),
                            ),
                          )))),
            const Spacer(),
            // Flexible(
            //   child: ListView(
            //       padding: const EdgeInsets.all(12.0),
            //       controller: listScrollController,
            //       children: list),
            // ),
          ],
        ),
      ),
    );
  }

  void _onDataReceived(Uint8List data) {
    // Allocate buffer for parsed data
    int backspacesCounter = 0;
    for (var byte in data) {
      if (byte == 8 || byte == 127) {
        backspacesCounter++;
      }
    }
    Uint8List buffer = Uint8List(data.length - backspacesCounter);
    int bufferIndex = buffer.length;

    // Apply backspace control character
    backspacesCounter = 0;
    for (int i = data.length - 1; i >= 0; i--) {
      if (data[i] == 8 || data[i] == 127) {
        backspacesCounter++;
      } else {
        if (backspacesCounter > 0) {
          backspacesCounter--;
        } else {
          buffer[--bufferIndex] = data[i];
        }
      }
    }

    // Create message if there is new line character
    String dataString = String.fromCharCodes(buffer);
    int index = buffer.indexOf(13);
    if (~index != 0) {
      setState(() {
        messages.add(
          _Message(
            1,
            backspacesCounter > 0
                ? _messageBuffer.substring(
                    0, _messageBuffer.length - backspacesCounter)
                : _messageBuffer + dataString.substring(0, index),
          ),
        );
        _messageBuffer = dataString.substring(index);
      });
    } else {
      _messageBuffer = (backspacesCounter > 0
          ? _messageBuffer.substring(
              0, _messageBuffer.length - backspacesCounter)
          : _messageBuffer + dataString);
    }
  }

  void _sendMessage(List<int> list) async {
    // textEditingController.clear();
    const int BytesEachTime = 10;
    if (list.length > 0) {
      try {
        setState(() {
          isSending = true;
        });

        for (int i = 0; i < list.length; i += BytesEachTime) {
          connection!.output.add(Uint8List.fromList(
              list.sublist(i, min(i + BytesEachTime, list.length))));
          await connection!.output.allSent;
          await Future.delayed(const Duration(milliseconds: 10));
        }

        setState(() {
          isSending = false;
        });
        // isSending = false;
        // setState(() {
        //   messages.add(_Message(clientID, text));
        // });

        // Future.delayed(Duration(milliseconds: 333)).then((_) {
        //   listScrollController.animateTo(
        //       listScrollController.position.maxScrollExtent,
        //       duration: Duration(milliseconds: 333),
        //       curve: Curves.easeOut);
        // });
      } catch (e) {
        // Ignore error, but notify state
        setState(() {});
      }
    }
  }

  // void _send_when_connected() {
  //   while (isConnected != true) {}
  //   globals.list_of_int_images.forEach((element) => _sendMessage(element));
  // }
}
