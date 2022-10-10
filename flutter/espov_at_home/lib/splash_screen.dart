import 'package:espov_at_home/bluetooth_connect.dart';
import 'package:flutter/material.dart';
class SplashScreen extends StatelessWidget {
  const SplashScreen({Key? key}) : super(key: key);
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      // appBar: AppBar(
      //   title: Text("hey"),
      // ),
      body:  Center(
      child:  Column(
        mainAxisAlignment: MainAxisAlignment.center,
        crossAxisAlignment: CrossAxisAlignment.center,
        mainAxisSize: MainAxisSize.min,
        children:  <Widget>[
          Spacer(),
            Text('ESPOV',
            style: TextStyle(fontFamily: 'Russo',fontSize: 60,  color: Color(0xff79d7dd)),
            ),
          Text('at home',
            style: TextStyle(fontFamily: 'Julius',fontSize: 30, color: Color(0xff79d7dd)),
          ),

          // new Container(
          //   child: new Image.asset(
          //     'assets/images/splash_logo.jpg',
          //     fit: BoxFit.cover,
          //   ),
          // ),
          Spacer(),
          TextButton(
              style: ButtonStyle(
                  backgroundColor: MaterialStatePropertyAll<Color>(Color(0xff79d7dd)),
                  shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                      RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(18.0),
                      )
                  )
              ),

              onPressed: () {
                Navigator.push(context, MaterialPageRoute(builder: (context) {
                  return const BluetoothConnect();
                }
                )
                );
              }
              ,
              child: const Text('   Get Started  ',style: TextStyle(color: Color(0xFFFFFFFF),),
            ),
          ),
          ],
        ),

    ),
    );
  }
}