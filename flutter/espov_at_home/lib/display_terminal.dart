import 'package:flutter/material.dart';
import 'package:espov_at_home/picking_text.dart';
import 'package:espov_at_home/picking_image.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';

class DisplayTerminal extends StatelessWidget {
  const DisplayTerminal({Key? key}) : super(key: key);
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.center,
            mainAxisSize: MainAxisSize.min,
            children: <Widget>[
              TextButton(
                style: ButtonStyle(
                    backgroundColor:
                        MaterialStatePropertyAll<Color>(Color(0xff79d7dd)),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                        RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(18.0),
                    ))),
                onPressed: () {
                  Navigator.push(context, MaterialPageRoute(builder: (context) {
                    return const PickingPhoto();
                  }));
                },
                child: const Text(
                  '   Choose Photos   ',
                  style: TextStyle(
                    color: Color(0xFFFFFFFF),
                  ),
                ),
              ),
              SizedBox(height: 40),
              TextButton(
                style: ButtonStyle(
                    backgroundColor:
                        MaterialStatePropertyAll<Color>(Color(0xff79d7dd)),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                        RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(18.0),
                    ))),
                onPressed: () {
                  Navigator.push(context, MaterialPageRoute(builder: (context) {
                    return const TextToPhoto();
                  }));
                },
                child: const Text(
                  '   Create text image   ',
                  style: TextStyle(
                    color: Color(0xFFFFFFFF),
                  ),
                ),
              ),
            ]),
      ),
    );
  }
}
