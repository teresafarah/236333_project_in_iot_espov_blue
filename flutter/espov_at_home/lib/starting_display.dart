import 'package:espov_at_home/bluetooth_connect.dart';
import 'package:espov_at_home/display_terminal.dart';
import 'package:flutter/material.dart';

import 'global_vars.dart' as globals;

// void _sendMessage(String text) async {
//   text = text.trim();
//   textEditingController.clear();
//
//   if (text.length > 0) {
//     try {
//       connectioni < globals.fileslist!.output.add(Uint8List.fromList(utf8.encode(text + "\r\n")));
//       await connection!.output.allSent;
//
//       setState(() {
//         messages.add(_Message(clientID, text));
//       });
//
//       Future.delayed(Duration(milliseconds: 333)).then((_) {
//         listScrollController.animateTo(
//             listScrollController.position.maxScrollExtent,
//             duration: Duration(milliseconds: 333),
//             curve: Curves.easeOut);
//       });
//     } catch (e) {
//       // Ignore error, but notify state
//       setState(() {});
//     }
//   }
// }

class StartingDisplay extends StatelessWidget {
  const StartingDisplay({Key? key}) : super(key: key);
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      // appBar: AppBar(
      //   title: Text("hey"),
      // ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          crossAxisAlignment: CrossAxisAlignment.center,
          mainAxisSize: MainAxisSize.min,
          children: <Widget>[
            Spacer(),
            TextButton(
              style: ButtonStyle(
                  backgroundColor:
                      MaterialStatePropertyAll<Color>(Color(0xff79d7dd)),
                  shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                      RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(18.0),
                  ))),
              onPressed: () {
                Navigator.pop(context);
                // Navigator.push(context, MaterialPageRoute(builder: (context) {
                //   return const DisplayTerminal();
                // }
                // )
                // );
              },
              child: const Text(
                '   Stop!  ',
                style: TextStyle(
                  color: Color(0xFFFFFFFF),
                ),
              ),
            ),
            Spacer(),
          ],
        ),
      ),
    );
  }
}
