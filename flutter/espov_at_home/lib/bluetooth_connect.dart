import 'package:flutter/material.dart';
import 'package:espov_at_home/display_terminal.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'package:espov_at_home/ChatPage.dart';
import 'package:espov_at_home/SelectBondedDevicePage.dart';
import 'global_vars.dart' as globals;

class BluetoothConnect extends StatelessWidget {
  const BluetoothConnect({Key? key}) : super(key: key);
  @override
  Widget build(BuildContext context) {
    return Scaffold(

      body: Center(
        child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.center,
            mainAxisSize: MainAxisSize.min,
          children:  <Widget>[
            TextButton(
              onPressed: () {
                FlutterBluetoothSerial.instance.openSettings();
              },              child: const Text('Pair up with ESPOV_ESP32'),
            ),
            TextButton(
              onPressed: () async {
                final BluetoothDevice? selectedDevice =
                await Navigator.of(context).push(
                  MaterialPageRoute(
                    builder: (context) {
                      return SelectBondedDevicePage(checkAvailability: false);
                    },
                  ),
                );

                if (selectedDevice != null) {
                  print('Connect -> selected ' + selectedDevice.address);
                  _startChat(context, selectedDevice);
                } else {
                  print('Connect -> no device selected');
                }
              },
              child: const Text('Next'),
            ),

          ]
        ),


      ),
    );
  }
}


void _startChat(BuildContext context, BluetoothDevice server) {


  globals.global_server = server;
  Navigator.of(context).push(
    MaterialPageRoute(
      builder: (context) {
        return DisplayTerminal();
      },
    ),
  );
}