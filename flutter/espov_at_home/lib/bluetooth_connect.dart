import 'package:flutter/material.dart';

class BluetoothConnect extends StatelessWidget {
  const BluetoothConnect({Key? key}) : super(key: key);
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("bluetooth connection"),
      ),
      body: Center(
        child: TextButton(
          onPressed: () {},
          child: const Text('Go Back'),
        ),
      ),
    );
  }
}
