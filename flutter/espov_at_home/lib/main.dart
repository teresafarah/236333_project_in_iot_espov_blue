import 'package:flutter/material.dart';
import './splash_screen.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        // This is the theme of your application.
        //
        // Try running your application with "flutter run". You'll see the
        // application has a blue toolbar. Then, without quitting the app, try
        // changing the primarySwatch below to Colors.green and then invoke
        // "hot reload" (press "r" in the console where you ran "flutter run",
        // or simply save your changes to "hot reload" in a Flutter IDE).
        // Notice that the counter didn't reset back to zero; the application
        // is not restarted.
        primarySwatch: Colors.blue,
        // scaffoldBackgroundColor: const Color(0xFFFFFFFF),
      ),
      home: const SplashScreen(),
    );
  }
}
//
// class MyHomePage extends StatefulWidget {
//   const MyHomePage({super.key, required this.title});
//
//   // This widget is the home page of your application. It is stateful, meaning
//   // that it has a State object (defined below) that contains fields that affect
//   // how it looks.
//
//   // This class is the configuration for the state. It holds the values (in this
//   // case the title) provided by the parent (in this case the App widget) and
//   // used by the build method of the State. Fields in a Widget subclass are
//   // always marked "final".
//
//   final String title;
//
//   @override
//   State<MyHomePage> createState() => _MyHomePageState();
// }
//
// class _MyHomePageState extends State<MyHomePage> {
//   int _counter = 0;
//
//   void _incrementCounter() {
//     setState(() {
//       // This call to setState tells the Flutter framework that something has
//       // changed in this State, which causes it to rerun the build method below
//       // so that the display can reflect the updated values. If we changed
//       // _counter without calling setState(), then the build method would not be
//       // called again, and so nothing would appear to happen.
//       _counter++;
//     });
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
//         // Center is a layout widget. It takes a single child and positions it
//         // in the middle of the parent.
//         child: Column(
//           // Column is also a layout widget. It takes a list of children and
//           // arranges them vertically. By default, it sizes itself to fit its
//           // children horizontally, and tries to be as tall as its parent.
//           //
//           // Invoke "debug painting" (press "p" in the console, choose the
//           // "Toggle Debug Paint" action from the Flutter Inspector in Android
//           // Studio, or the "Toggle Debug Paint" command in Visual Studio Code)
//           // to see the wireframe for each widget.
//           //
//           // Column has various properties to control how it sizes itself and
//           // how it positions its children. Here we use mainAxisAlignment to
//           // center the children vertically; the main axis here is the vertical
//           // axis because Columns are vertical (the cross axis would be
//           // horizontal).
//           mainAxisAlignment: MainAxisAlignment.center,
//           children: <Widget>[
//             const Text(
//               'You have pushed the button this many times:',
//             ),
//             Text(
//               '$_counter',
//               style: Theme.of(context).textTheme.headline4,
//             ),
//           ],
//         ),
//       ),
//       floatingActionButton: FloatingActionButton(
//         onPressed: _incrementCounter,
//         tooltip: 'Increment',
//         child: const Icon(Icons.add),
//       ), // This trailing comma makes auto-formatting nicer for build methods.
//     );
//   }
// }
//
//
//
// import 'dart:typed_data';
// import 'dart:io';
// import 'package:flutter/material.dart';
// import 'package:screenshot/screenshot.dart';
// // import 'package:webview_flutter/webview_flutter.dart';
// // import 'package:image_gallery_saver/image_gallery_saver.dart';
//
// void main() => runApp(MyApp());
//
// class MyApp extends StatelessWidget {
//   // This widget is the root of your application.
//   @override
//   Widget build(BuildContext context) {
//     return MaterialApp(
//       title: 'Flutter Demo',
//       theme: ThemeData(
//         textTheme: TextTheme(
//             headline6: TextStyle(
//               color: Colors.yellow,
//               fontSize: 50,
//             )),
//         // This is the theme of your application.
//         //
//         // Try running your application with "flutter run". You'll see the
//         // application has a blue toolbar. Then, without quitting the app, try
//         // changing the primarySwatch below to Colors.green and then invoke
//         // "hot reload" (press "r" in the console where you ran "flutter run",
//         // or simply save your changes to "hot reload" in a Flutter IDE).
//         // Notice that the counter didn't reset back to zero; the application
//         // is not restarted.
//         primarySwatch: Colors.blue,
//       ),
//       home: MyHomePage(title: 'Screenshot Demo Home Page'),
//     );
//   }
// }
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

//
// import 'dart:async';
// import 'dart:typed_data';
// import 'dart:ui' as ui;
// import 'package:flutter/material.dart';
//
// import 'package:dio/dio.dart';
// import 'package:flutter/rendering.dart';
// import 'package:fluttertoast/fluttertoast.dart';
// import 'package:image_gallery_saver/image_gallery_saver.dart';
// import 'package:path_provider/path_provider.dart';
// import 'package:permission_handler/permission_handler.dart';
//
// void main() => runApp(MyApp());
//
// class MyApp extends StatelessWidget {
//   @override
//   Widget build(BuildContext context) {
//     return MaterialApp(
//       title: 'Save image to gallery',
//       theme: ThemeData(
//         primarySwatch: Colors.blue,
//       ),
//       home: MyHomePage(),
//     );
//   }
// }
//
// class MyHomePage extends StatefulWidget {
//   @override
//   _MyHomePageState createState() => _MyHomePageState();
// }
//
// class _MyHomePageState extends State<MyHomePage> {
//   GlobalKey _globalKey = GlobalKey();
//
//   @override
//   void initState() {
//     super.initState();
//
//     _requestPermission();
//
//   }
//
//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//         appBar: AppBar(
//           title: Text("Save image to gallery"),
//         ),
//         body: Center(
//           child: Column(
//             children: <Widget>[
//               RepaintBoundary(
//                 key: _globalKey,
//                 child: Container(
//                   width: 200,
//                   height: 200,
//                   color: Colors.red,
//                 ),
//               ),
//               Container(
//                 padding: EdgeInsets.only(top: 15),
//                 child: TextButton(
//                   onPressed: _saveScreen,
//                   child: Text("Save Local Image"),
//                 ),
//                 width: 200,
//                 height: 44,
//               ),
//               Container(
//                 padding: EdgeInsets.only(top: 15),
//                 child: TextButton(
//                   onPressed: _getHttp,
//                   child: Text("Save network image"),
//                 ),
//                 width: 200,
//                 height: 44,
//               ),
//               Container(
//                 padding: EdgeInsets.only(top: 15),
//                 child: TextButton(
//                   onPressed: _saveVideo,
//                   child: Text("Save network video"),
//                 ),
//                 width: 200,
//                 height: 44,
//               ),
//               Container(
//                 padding: EdgeInsets.only(top: 15),
//                 child: TextButton(
//                   onPressed: _saveGif,
//                   child: Text("Save Gif to gallery"),
//                 ),
//                 width: 200,
//                 height: 44,
//               ),
//             ],
//           ),
//         ));
//   }
//
//   _requestPermission() async {
//     Map<Permission, PermissionStatus> statuses = await [
//       Permission.storage,
//     ].request();
//
//     final info = statuses[Permission.storage].toString();
//     print(info);
//     _toastInfo(info);
//   }
//
//   _saveScreen() async {
//     RenderRepaintBoundary boundary =
//     _globalKey.currentContext!.findRenderObject() as RenderRepaintBoundary;
//     ui.Image image = await boundary.toImage();
//     ByteData? byteData = await (image.toByteData(format: ui.ImageByteFormat.png));
//     if (byteData != null) {
//       final result =
//       await ImageGallerySaver.saveImage(byteData.buffer.asUint8List());
//       print(result);
//       _toastInfo(result.toString());
//     }
//   }
//
//   _getHttp() async {
//     var response = await Dio().get(
//         "https://ss0.baidu.com/94o3dSag_xI4khGko9WTAnF6hhy/image/h%3D300/sign=a62e824376d98d1069d40a31113eb807/838ba61ea8d3fd1fc9c7b6853a4e251f94ca5f46.jpg",
//         options: Options(responseType: ResponseType.bytes));
//     final result = await ImageGallerySaver.saveImage(
//         Uint8List.fromList(response.data),
//         quality: 60,
//         name: "hello");
//     print(result);
//     _toastInfo("$result");
//   }
//
//   _saveGif() async {
//     var appDocDir = await getTemporaryDirectory();
//     String savePath = appDocDir.path + "/temp.gif";
//     String fileUrl =
//         "https://hyjdoc.oss-cn-beijing.aliyuncs.com/hyj-doc-flutter-demo-run.gif";
//     await Dio().download(fileUrl, savePath);
//     final result = await ImageGallerySaver.saveFile(savePath);
//     print(result);
//     _toastInfo("$result");
//   }
//
//   _saveVideo() async {
//     var appDocDir = await getTemporaryDirectory();
//     String savePath = appDocDir.path + "/temp.mp4";
//     String fileUrl =
//         "http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/ForBiggerBlazes.mp4";
//     await Dio().download(fileUrl, savePath, onReceiveProgress: (count, total) {
//       print((count / total * 100).toStringAsFixed(0) + "%");
//     });
//     final result = await ImageGallerySaver.saveFile(savePath);
//     print(result);
//     _toastInfo("$result");
//   }
//
//   _toastInfo(String info) {
//     Fluttertoast.showToast(msg: info, toastLength: Toast.LENGTH_LONG);
//   }
// }
