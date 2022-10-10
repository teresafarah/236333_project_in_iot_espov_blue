
import 'package:flutter/material.dart';
import 'package:espov_at_home/picking_text.dart';
import 'package:espov_at_home/picking_image.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';

class DisplayTerminal extends StatelessWidget {
  final BluetoothDevice server;
  const DisplayTerminal({required this.server});
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
                  Navigator.push(context, MaterialPageRoute(builder: (context) {
                    return PickingPhoto(server : server);
                  }));
                },
                child: const Text('Choose a Photo'),
              ),
              TextButton(
                onPressed: () {
                  Navigator.push(context, MaterialPageRoute(builder: (context) {
                    return const PickingText();
                  }));
                },
                child: const Text('Choose a Text'),
              ),

            ]
        ),


      ),
    );
  }
}
