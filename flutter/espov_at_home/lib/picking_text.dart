import 'package:flutter/material.dart';
import 'package:auto_size_text_field/auto_size_text_field.dart';
import 'package:flutter/material.dart';
import 'dart:async';
import 'dart:typed_data';
import 'dart:ui' as ui;
import 'package:flutter/material.dart';
import 'package:flutter/rendering.dart';
import 'package:flutter/services.dart';
import 'package:path_provider/path_provider.dart';
import 'dart:io';
import 'dart:async';
import 'dart:typed_data';
import 'dart:ui' as ui;
import 'package:flutter/material.dart';

import 'package:dio/dio.dart';
import 'package:flutter/rendering.dart';
import 'package:fluttertoast/fluttertoast.dart';
import 'package:image_gallery_saver/image_gallery_saver.dart';
import 'package:path_provider/path_provider.dart';
import 'package:permission_handler/permission_handler.dart';
import 'package:screenshot/screenshot.dart';

// class PickingText extends StatelessWidget {
//   const PickingText({Key? key}) : super(key: key);
//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       body: Center(
//         child: Column(
//             mainAxisAlignment: MainAxisAlignment.center,
//             crossAxisAlignment: CrossAxisAlignment.center,
//             mainAxisSize: MainAxisSize.min,
//             children: <Widget>[
//               MyCustomForm(),
//             ]),
//       ),
//     );
//   }
// }
//
// class MyCustomForm extends StatelessWidget {
//   const MyCustomForm({Key? key}) : super(key: key);
//
//   @override
//   Widget build(BuildContext context) {
//     return Column(
//       crossAxisAlignment: CrossAxisAlignment.start,
//       children: <Widget>[
//         const Padding(
//           padding: EdgeInsets.symmetric(horizontal: 8, vertical: 16),
//           child: TextField(
//             decoration: InputDecoration(
//               border: OutlineInputBorder(),
//               hintText: 'Enter a simple text',
//             ),
//           ),
//         ),
//       ],
//     );
//   }
// }
//
// //
//
//
// class CustomTextBar extends StatefulWidget {
//   @override
//   _State createState() => _State();
// }
//
// class _State extends State<CustomTextBar> {
//   double custFontSize = 20;
//   Color color = Colors.white;
//   void IncreaseFontSize() async{
//     setState(() {
//       if (custFontSize + 2 >= 200){
//         custFontSize = 200;
//         return;
//       }
//       custFontSize+=2;
//     });
//   }
//   void DecreaseFontSize() async{
//     setState(() {
//       if (custFontSize - 2 <0){
//         custFontSize = 0;
//         return;
//       }
//       custFontSize-=2;
//     });
//   }
//
//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       body: Center(
//           child: Column(children: <Widget>[
//             Padding(
//               padding: EdgeInsets.symmetric(horizontal: 8, vertical: 16),
//               child: TextField(
//                 style: TextStyle(
//                     fontSize: custFontSize,
//                   color : Colors.green,
//                 ),
//                 decoration: InputDecoration(
//                   border: OutlineInputBorder(),
//                 ),
//               ),
//             ),
//             TextButton(
//               onPressed: () {
//                 IncreaseFontSize();
//               },
//               child: Text('Increase Font Size'),
//             ),
//             TextButton(
//               onPressed: () {
//                 DecreaseFontSize();
//               },
//               child: Text('Decrease Font Size'),
//             ),
//
//
//
//           ])),
//     );
//   }
// }

class TextToPhoto extends StatefulWidget {
  const TextToPhoto({Key? key}) : super(key: key);

  @override
  _TextToPhoto createState() => _TextToPhoto();
}

class _TextToPhoto extends State<TextToPhoto> {
  final fieldText = TextEditingController();
  Color custFontColor = Color(0xff79d7dd);
  double custFontSize = 20;
  FontWeight custWeight = FontWeight.normal;
  GlobalKey _globalKey = GlobalKey();
  ScreenshotController screenshotController = ScreenshotController();

  void changeFontWeight() async {
    setState(() {
      if (custWeight == FontWeight.normal) {
        custWeight = FontWeight.bold;
        return;
      } else {
        custWeight = FontWeight.normal;
        return;
      }
    });
  }

  void changeColorToRed() async {
    setState(() {
      custFontColor = Colors.red;
    });
  }

  void changeColorToGreen() async {
    setState(() {
      custFontColor = Colors.green;
    });
  }

  void changeColorToBlue() async {
    setState(() {
      custFontColor = Colors.blue;
    });
  }

  void changeColorToYellow() async {
    setState(() {
      custFontColor = Colors.yellow;
    });
  }

  void changeColorToTeal() async {
    setState(() {
      custFontColor = Color(0xff79d7dd);
    });
  }

  void changeColorToDeepOrange() async {
    setState(() {
      custFontColor = Colors.deepOrange;
    });
  }

  void changeColorToPink() async {
    setState(() {
      custFontColor = Colors.pink;
    });
  }

  void IncreaseFontSize() async {
    setState(() {
      if (custFontSize + 2 >= 200) {
        custFontSize = 200;
        return;
      }
      custFontSize += 2;
    });
  }

  void DecreaseFontSize() async {
    setState(() {
      if (custFontSize - 2 < 0) {
        custFontSize = 0;
        return;
      }
      custFontSize -= 2;
    });
  }

  void clearText() {
    fieldText.clear();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: SingleChildScrollView(
        child: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              SizedBox(height: 150),
              Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: <Widget>[
                  IconButton(
                    icon: Icon(Icons.add_circle),
                    color: Color(0xff79d7dd),
                    onPressed: () {
                      IncreaseFontSize();
                    },
                  ),
                  IconButton(
                    icon: Icon(Icons.remove_circle),
                    color: Color(0xff79d7dd),
                    onPressed: () {
                      DecreaseFontSize();
                    },
                  ),
                ],
              ),
              IconButton(
                icon: Icon(Icons.format_bold),
                color: Color(0xff79d7dd),
                onPressed: () {
                  changeFontWeight();
                },
              ),
              Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: <Widget>[
                  IconButton(
                    icon: Icon(Icons.circle),
                    color: Colors.blue,
                    onPressed: () {
                      changeColorToBlue();
                    },
                  ),
                  IconButton(
                    icon: Icon(Icons.circle),
                    color: Colors.red,
                    onPressed: () {
                      changeColorToRed();
                    },
                  ),
                  IconButton(
                    icon: Icon(Icons.circle),
                    color: Colors.green,
                    onPressed: () {
                      changeColorToGreen();
                    },
                  ),
                  IconButton(
                    icon: Icon(Icons.circle),
                    color: Colors.yellow,
                    onPressed: () {
                      changeColorToYellow();
                    },
                  ),
                  IconButton(
                    icon: Icon(Icons.circle),
                    color: Color(0xff79d7dd),
                    onPressed: () {
                      changeColorToTeal();
                    },
                  ),
                  IconButton(
                    icon: Icon(Icons.circle),
                    color: Colors.pink,
                    onPressed: () {
                      changeColorToPink();
                    },
                  ),
                  IconButton(
                    icon: Icon(Icons.circle),
                    color: Colors.deepOrange,
                    onPressed: () {
                      changeColorToDeepOrange();
                    },
                  ),
                ],
              ),
              Padding(
                padding: const EdgeInsets.symmetric(vertical: 24.0),
                child: Container(
                  decoration: BoxDecoration(
                    color: Colors.black,
                    border: Border.all(width: 4, color: Color(0xff79d7dd)),
                    borderRadius: BorderRadius.all(Radius.circular(20)),
                  ),
                  constraints: BoxConstraints(
                      maxHeight: 300,
                      maxWidth: 300,
                      minHeight: 300,
                      minWidth: 300),
                  // decoration: BoxDecoration(
                  //     // color: Colors.black,
                  //     border: Border.all(width: 4, color: Color(0xff79d7dd)),
                  //     borderRadius: BorderRadius.all(Radius.circular(20))),
                  child: Screenshot(
                    controller: screenshotController,
                    child: SizedBox(
                      height: 300,
                      width: 300,
                      child: TextField(
                        controller: fieldText,
                        keyboardType: TextInputType.multiline,
                        maxLines: null,
                        cursorColor: Colors.transparent,
                        style: TextStyle(
                          fontSize: custFontSize,
                          color: custFontColor,
                          fontWeight: custWeight,
                        ),
                        decoration: InputDecoration(
                          border: InputBorder.none,
                        ),
                      ),
                    ),
                  ),
                ),
              ),
              TextButton(
                style: ButtonStyle(
                    backgroundColor:
                        MaterialStatePropertyAll<Color>(Color(0xff79d7dd)),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                        RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(18.0),
                    ))),
                onPressed: clearText,
                child: const Text(
                  '   clear   ',
                  style: TextStyle(
                    color: Color(0xFFFFFFFF),
                  ),
                ),
              ),
              TextButton(
                style: ButtonStyle(
                    backgroundColor:
                        MaterialStatePropertyAll<Color>(Color(0xff79d7dd)),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                        RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(18.0),
                    ))),
                onPressed: () {
                  screenshotController
                      .capture(delay: Duration(milliseconds: 10))
                      .then((capturedImage) async {
                    ShowCapturedWidget(context, capturedImage!);
                  }).catchError((onError) {
                    print(onError);
                  });
                },
                child: const Text(
                  '   display   ',
                  style: TextStyle(
                    color: Color(0xFFFFFFFF),
                  ),
                ),
              ),
            ],
          ),
        ),
      ), // This trailing comma makes auto-formattig nicer for build methods.
    );
  }

  @override
  void initState() {
    super.initState();
  }

  @override
  void dispose() {
    super.dispose();
  }

  _saveScreen() async {
    RenderRepaintBoundary boundary =
        _globalKey.currentContext!.findRenderObject() as RenderRepaintBoundary;
    ui.Image image = await boundary.toImage();
    ByteData? byteData =
        await (image.toByteData(format: ui.ImageByteFormat.png));
    if (byteData != null) {
      final result =
          await ImageGallerySaver.saveImage(byteData.buffer.asUint8List());
      print(result);
      _toastInfo(result.toString());
    }
  }

  _toastInfo(String info) {
    Fluttertoast.showToast(msg: info, toastLength: Toast.LENGTH_LONG);
  }

  Future<dynamic> ShowCapturedWidget(
      BuildContext context, Uint8List capturedImage) {
    return showDialog(
        useSafeArea: false,
        context: context,
        builder: (context) => Scaffold(
              body: Center(
                child: Column(
                  children: <Widget>[
                    Spacer(),
                    Container(
                      width: 300,
                      height: 300,
                      decoration: BoxDecoration(
                        color: Colors.black,
                        border: Border.all(color: Color(0xff79d7dd), width: 4),
                        borderRadius: BorderRadius.all(Radius.circular(20)),
                      ),
                      // color: Colors.black,
                      child: RepaintBoundary(
                          key: _globalKey,
                          child: capturedImage != null
                              ? Image.memory(capturedImage)
                              : Container()),
                    ),
                    TextButton(
                      style: ButtonStyle(
                          backgroundColor: MaterialStatePropertyAll<Color>(
                              Color(0xff79d7dd)),
                          shape:
                              MaterialStateProperty.all<RoundedRectangleBorder>(
                                  RoundedRectangleBorder(
                            borderRadius: BorderRadius.circular(18.0),
                          ))),
                      onPressed: () {
                        _saveScreen();
                        Navigator.pop(context);
                        Navigator.pop(context);
                      },
                      child: const Text(
                        '   save   ',
                        style: TextStyle(
                          color: Color(0xFFFFFFFF),
                        ),
                      ),
                    ),
                    Spacer(),
                  ],
                ),
              ),
            ));
  }
}



//
// import 'dart:typed_data';
// import 'dart:io';
// import 'package:flutter/material.dart';
// import 'package:screenshot/screenshot.dart';
// // import 'package:webview_flutter/webview_flutter.dart';
// // import 'package:image_gallery_saver/image_gallery_saver.dart';
//
//
//
// class MyHomePage extends StatefulWidget {
//   MyHomePage({Key? key, required this.title}) : super(key: key);
//   final String title;
//
//   @override
//   _MyHomePageState createState() => _MyHomePageState();
// }
//
// class _MyHomePageState extends State<MyHomePage> {
//   //Create an instance of ScreenshotController
//   ScreenshotController screenshotController = ScreenshotController();
//
//   @override
//   void initState() {
//     // if (Platform.isAndroid) WebView.platform = SurfaceAndroidWebView();
//     super.initState();
//   }
//
//   @override
//   Widget build(BuildContext context) {
//     // This method is rerun every time setState is called, for instance as done
//     // by the _incrementCounter method above.
//     //
//     // The Flutter framework has been optimized to make rerunning build methods
//     // fast, so that you can just rebuild anything that needs updating rather
//     // than having to individually change instances of widgets.
//     return Scaffold(
//       appBar: AppBar(
//         // Here we take the value from the MyHomePage object that was created by
//         // the App.build method, and use it to set our appbar title.
//         title: Text(widget.title),
//       ),
//       body: Center(
//         child: Column(
//           mainAxisAlignment: MainAxisAlignment.center,
//           children: [
//             Screenshot(
//               controller: screenshotController,
//               child: Container(
//                   padding: const EdgeInsets.all(30.0),
//                   decoration: BoxDecoration(
//                     border: Border.all(color: Colors.blueAccent, width: 5.0),
//                     color: Colors.amberAccent,
//                   ),
//                   child: Text("This widget will be captured as an image")),
//             ),
//             SizedBox(
//               height: 25,
//             ),
//             ElevatedButton(
//               child: Text(
//                 'Capture Above Widget',
//               ),
//               onPressed: () {
//                 screenshotController
//                     .capture(delay: Duration(milliseconds: 10))
//                     .then((capturedImage) async {
//                   ShowCapturedWidget(context, capturedImage!);
//                 }).catchError((onError) {
//                   print(onError);
//                 });
//               },
//             ),
//             ElevatedButton(
//               child: Text(
//                 'Capture An Invisible Widget',
//               ),
//               onPressed: () {
//                 var container = Container(
//                     padding: const EdgeInsets.all(30.0),
//                     decoration: BoxDecoration(
//                       border: Border.all(color: Colors.blueAccent, width: 5.0),
//                       color: Colors.redAccent,
//                     ),
//                     child: Text(
//                       "This is an invisible widget",
//                       style: Theme.of(context).textTheme.headline6,
//                     ));
//                 screenshotController
//                     .captureFromWidget(
//                     InheritedTheme.captureAll(
//                         context, Material(child: container)),
//                     delay: Duration(seconds: 1))
//                     .then((capturedImage) {
//                   ShowCapturedWidget(context, capturedImage);
//                 });
//               },
//             ),
//           ],
//         ),
//       ),
//     );
//   }
//
//   Future<dynamic> ShowCapturedWidget(
//       BuildContext context, Uint8List capturedImage) {
//     return showDialog(
//       useSafeArea: false,
//       context: context,
//       builder: (context) => Scaffold(
//         appBar: AppBar(
//           title: Text("Captured widget screenshot"),
//         ),
//         body: Center(
//             child: capturedImage != null
//                 ? Image.memory(capturedImage)
//                 : Container()),
//       ),
//     );
//
//
//   }
//
//
// }





