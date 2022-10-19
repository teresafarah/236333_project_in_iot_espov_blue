import 'package:flutter/material.dart';
import 'package:flutter/material.dart';
import 'package:espov_at_home/picking_text.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'dart:io';
import 'dart:math';
import 'package:espov_at_home/ChatPage.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:image_picker/image_picker.dart';
import 'package:flutter_native_image/flutter_native_image.dart';
import 'package:image/image.dart' as Imagi;
import 'dart:typed_data'; //Bundled with Dart
import 'global_vars.dart' as globals;

import 'package:espov_at_home/starting_display.dart';

// var fileslist = List<File>.empty(growable: true);

//pick image from prev app attempt////////////////////////////////////////////
// class PhotoChoice extends StatefulWidget {
//   const PhotoChoice();
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
//
//   @override
//   State<PhotoChoice> createState() => _PhotoChoiceState();
// }
//
// class _PhotoChoiceState extends State<PhotoChoice> {
//
//   File? image;
//
//   Future pickImage() async {
//     try {
//       final image = await ImagePicker().pickImage(source: ImageSource.gallery);
//
//       if(image == null) return;
//
//       final imageTemp = File(image.path);
//
//       setState(() => this.image = imageTemp);
//
//       //find wigth and height part
//       var tmp_decoded = await decodeImageFromList(imageTemp.readAsBytesSync());
//       int my_width = tmp_decoded.width;
//       int my_height = tmp_decoded.height;
//       print('printing width and height');
//       print(my_width);
//       print(my_height);
//
//       // resize
//       ImageProperties properties = await FlutterNativeImage.getImageProperties(image.path);
//       File compressedFile = await FlutterNativeImage.compressImage(image.path,quality: 100,
//           targetWidth: 63,
//           targetHeight: 63);
//
//       final compressed_image_temp = compressedFile;
//       var tmp_comp_decoded = await decodeImageFromList(compressed_image_temp.readAsBytesSync());
//       int my_comp_width = tmp_comp_decoded.width;
//       int my_comp_height = tmp_comp_decoded.height;
//       print('printing compressed width and height');
//       print(my_comp_width);
//       print(my_comp_height);
//
//
//
//       final inputImg = await compressed_image_temp.readAsBytes(); // Converts the file to UInt8List
//
//       final decoder = Imagi.JpegDecoder();
//       final decodedImg = decoder.decodeImage(inputImg);
//       final decodedBytes = decodedImg!.getBytes(format: Imagi.Format.rgb);
//
//       List<List<List<int>>> imgArr = [] ;
//       assert(decodedImg != null);
//       for(int y = 0; y < decodedImg!.height; y++) {
//         imgArr.add([]);
//         for(int x = 0; x < decodedImg!.width; x++) {
//           int red = decodedBytes[y*decodedImg.width*3 + x*3];
//           int green = decodedBytes[y*decodedImg.width*3 + x*3 + 1];
//           int blue = decodedBytes[y*decodedImg.width*3 + x*3 + 2];
//           imgArr[y].add([red, green, blue]);
//           print([red,green,blue]);
//         }
//       }
//       print('printing imgArr.length');
//
//
//
//
//
//
//
//
//       setState(() => this.image = compressed_image_temp);
//
//
//
//
//
//
//
//
//     } on PlatformException catch(e) {
//       print('Failed to pick image: $e');
//     }
//
//
//
//   }
//
//   Future pickImageC() async {
//     try {
//       final image = await ImagePicker().pickImage(source: ImageSource.camera);
//
//       if(image == null) return;
//
//       final imageTemp = File(image.path);
//
//       setState(() => this.image = imageTemp);
//     } on PlatformException catch(e) {
//       print('Failed to pick image: $e');
//     }
//
//   }
//
//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//         appBar: AppBar(
//           title: const Text("Image Picker Example"),
//         ),
//         body: Center(
//           child: Column(
//             children: [
//               MaterialButton(
//                   color: Colors.blue,
//                   child: const Text(
//                       "Pick Image from Gallery",
//                       style: TextStyle(
//                           color: Colors.white70, fontWeight: FontWeight.bold
//                       )
//                   ),
//                   onPressed: () {
//                     pickImage();
//                   }
//               ),
//               MaterialButton(
//                   color: Colors.blue,
//                   child: const Text(
//                       "Pick Image from Camera",
//                       style: TextStyle(
//                           color: Colors.white70, fontWeight: FontWeight.bold
//                       )
//                   ),
//                   onPressed: () {
//                     pickImageC();
//                   }
//               ),
//               SizedBox(height: 20,),
//               image != null ? Image.file(image!): Text("No image selected")
//             ],
//           ),
//         )
//     );
//   }
// }
// // end of attempt//////////////////////////////////////////////////////////////
//
//
//
//
//
//

class PickingPhoto extends StatelessWidget {
  const PickingPhoto({Key? key}) : super(key: key);
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: AnimatedListSample(),
      ),
    );
  }
}

//
// void main() {
//   runApp(const AnimatedListSample());
// }

class AnimatedListSample extends StatefulWidget {
  const AnimatedListSample({super.key});

  @override
  State<AnimatedListSample> createState() => _AnimatedListSampleState();
}

class _AnimatedListSampleState extends State<AnimatedListSample> {
  ///////////////////////////////////////////
  File image = File('');

  Future pickImage() async {
    try {
      final image = await ImagePicker().pickImage(source: ImageSource.gallery);

      if (image == null) return;

      final imageTemp = File(image.path);

      setState(() => this.image = imageTemp);

      //find wigth and height part
      var tmp_decoded = await decodeImageFromList(imageTemp.readAsBytesSync());
      int my_width = tmp_decoded.width;
      int my_height = tmp_decoded.height;

      // resize
      ImageProperties properties =
          await FlutterNativeImage.getImageProperties(image.path);
      File compressedFile = await FlutterNativeImage.compressImage(image.path,
          quality: 100, targetWidth: 63, targetHeight: 63);

      final compressed_image_temp = compressedFile;
      var tmp_comp_decoded =
          await decodeImageFromList(compressed_image_temp.readAsBytesSync());
      int my_comp_width = tmp_comp_decoded.width;
      int my_comp_height = tmp_comp_decoded.height;

      final inputImg = await compressed_image_temp
          .readAsBytes(); // Converts the file to UInt8List

      final decoder = Imagi.JpegDecoder();
      final decodedImg = decoder.decodeImage(inputImg);
      final decodedBytes = decodedImg!.getBytes(format: Imagi.Format.rgb);

      // List<List<List<int>>> imgArr = [] ;
      List<int> red_list = [];
      List<int> green_list = [];
      List<int> blue_list = [];

      assert(decodedImg != null);
      for (int y = 0; y < decodedImg!.height; y++) {
        // imgArr.add([]);
        for (int x = 0; x < decodedImg!.width; x++) {
          int red = decodedBytes[y * decodedImg.width * 3 + x * 3];
          int green = decodedBytes[y * decodedImg.width * 3 + x * 3 + 1];
          int blue = decodedBytes[y * decodedImg.width * 3 + x * 3 + 2];
          // imgArr[y].add([red, green, blue]);
          red_list.add(red);
          green_list.add(green);
          blue_list.add(blue);
          // print([red, green, blue]);
        }
      }
      List<int> rgb_list = []
        ..addAll(red_list)
        ..addAll(green_list)
        ..addAll(blue_list);
      // print(rgb_list.length);
      final int index =
          _selectedItem == null ? _list.length : _list.indexOf(_selectedItem!);
      // for (int i = 0 ; i < rgb_list.length ; i++){
      //   rgb_list[i] = (rgb_list[i] / 2).round();
      // }
      globals.list_of_int_images.insert(index, rgb_list);

      setState(() => this.image = compressed_image_temp);
    } on PlatformException catch (e) {
      print('Failed to pick image: $e');
    }

    _insert();
  }
  ////////////////////////////////////////////

  final GlobalKey<AnimatedListState> _listKey = GlobalKey<AnimatedListState>();
  late ListModel<int> _list;
  int? _selectedItem;
  late int
      _nextItem; // The next item inserted when the user presses the '+' button.

  @override
  void initState() {
    globals.fileslist = List<File>.empty(growable: true);
    globals.list_of_int_images = List<List<int>>.empty(growable: true);

    super.initState();
    _list = ListModel<int>(
      listKey: _listKey,
      initialItems: <int>[],
      removedItemBuilder: _buildRemovedItem,
    );
    _nextItem = 0;
  }

  // Used to build list items that haven't been removed.
  Widget _buildItem(
      BuildContext context, int index, Animation<double> animation) {
    return CardItem(
      animation: animation,
      item: index,
      selected: _selectedItem == _list[index],
      // onTap: () {
      //   setState(() {
      //     _selectedItem = _selectedItem == _list[index] ? null : _list[index];
      //   });
      // },
    );
  }

  // Used to build an item after it has been removed from the list. This
  // method is needed because a removed item remains visible until its
  // animation has completed (even though it's gone as far this ListModel is
  // concerned). The widget will be used by the
  // [AnimatedListState.removeItem] method's
  // [AnimatedListRemovedItemBuilder] parameter.
  Widget _buildRemovedItem(
      int item, BuildContext context, Animation<double> animation) {
    return CardItem(
      animation: animation,
      item: item,
      // No gesture detector here: we don't want removed items to be interactive.
    );
  }

  // Insert the "next item" into the list model.
  void _insert() {
    final int index =
        _selectedItem == null ? _list.length : _list.indexOf(_selectedItem!);
    _list.insert(index, _nextItem++);
    globals.fileslist.insert(index, this.image);
  }

  // Remove the selected item from the list model.
  void _remove() {
    if (_selectedItem != null) {
      _list.removeAt(_list.indexOf(_selectedItem!));
      setState(() {
        _selectedItem = null;
      });
    }

    globals.fileslist.removeAt(_list.indexOf(_selectedItem!));
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text(
            '',
          ),
          // backgroundColor : Color(0xff79d7dd),
          backgroundColor: Colors.transparent,
          elevation: 0,
          // shadowColor: Colors.white,
          actions: <Widget>[
            Spacer(),
            Container(
              height: 50,
              width: 50,
              alignment: Alignment.center,
              child: TextButton(
                style: ButtonStyle(
                    backgroundColor:
                        MaterialStatePropertyAll<Color>(Color(0xff79d7dd)),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                        RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(18.0),
                    ))),
                onPressed: () {
                  // globals.fileslist = List<File>.empty(growable: true);

                  Navigator.pop(context);
                  Navigator.push(context, MaterialPageRoute(builder: (context) {
                    return ChatPage(server: globals.global_server);
                  }));
                },
                child: const Text('done',
                    style: TextStyle(
                      color: Color(0xFFFFFFFF),
                    )),
              ),
            ),
            Spacer(),
            IconButton(
              color: Color(0xff79d7dd),
              icon: const Icon(Icons.add_circle),
              iconSize: 45,
              onPressed: pickImage,
              tooltip: 'insert a new item',
            ),
            // Spacer(),
            //
            // IconButton(
            //   icon: const Icon(Icons.remove_circle),
            //   color: Color(0xff79d7dd),
            //   iconSize: 45,
            //   onPressed: _remove,
            //   tooltip: 'remove the selected item',
            // ),
            Spacer(),
            Container(
              height: 50,
              width: 50,
              alignment: Alignment.center,
              child: TextButton(
                style: ButtonStyle(
                    backgroundColor:
                        MaterialStatePropertyAll<Color>(Color(0xff79d7dd)),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                        RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(18.0),
                    ))),
                onPressed: () {
                  globals.fileslist = List<File>.empty(growable: true);
                  globals.list_of_int_images =
                      List<List<int>>.empty(growable: true);

                  Navigator.pop(context);
                  Navigator.push(context, MaterialPageRoute(builder: (context) {
                    return const PickingPhoto();
                  }));
                },
                child: const Text('reset',
                    style: TextStyle(
                      color: Color(0xFFFFFFFF),
                    )),
              ),
            ),

            // TextButton(
            //   style: ButtonStyle(
            //       backgroundColor: MaterialStatePropertyAll<Color>(Color(0xff79d7dd)),
            //       shape: MaterialStateProperty.all<RoundedRectangleBorder>(
            //           RoundedRectangleBorder(
            //             borderRadius: BorderRadius.circular(100.0),
            //           )
            //       )
            //   ),
            //   onPressed: () {
            //   },
            //   child: const Text('reset',style: TextStyle(color: Color(0xFFFFFFFF),)),
            // ),
            Spacer(),
          ],
        ),
        body: Padding(
          padding: const EdgeInsets.all(16.0),
          child: AnimatedList(
            key: _listKey,
            initialItemCount: _list.length,
            itemBuilder: _buildItem,
          ),
        ),
        // body: Center(
        //   child: Column(
        //       mainAxisAlignment: MainAxisAlignment.center,
        //       crossAxisAlignment: CrossAxisAlignment.center,
        //       mainAxisSize: MainAxisSize.min,
        //       children:  <Widget>[
        //
        //
        //   Padding(
        //       padding: const EdgeInsets.all(16.0),
        //       child: AnimatedList(
        //         key: _listKey,
        //         initialItemCount: _list.length,
        //         itemBuilder: _buildItem,
        //       ),
        //   ),
        //         IconButton(
        //           icon: const Icon(Icons.add_circle),
        //           iconSize: 45,
        //           color: Color(0xff79d7dd),
        //           onPressed: pickImage,
        //           tooltip: 'insert a new item',
        //         ),
        //         IconButton(
        //           icon: const Icon(Icons.remove_circle),
        //           color: Color(0xff79d7dd),
        //           iconSize: 45,
        //           onPressed: _remove,
        //           tooltip: 'remove the selected item',
        //         ),
        //
        //         ],
        //   )
        // )
      ),
    );
  }
}

typedef RemovedItemBuilder<T> = Widget Function(
    T item, BuildContext context, Animation<double> animation);

/// Keeps a Dart [List] in sync with an [AnimatedList].
///
/// The [insert] and [removeAt] methods apply to both the internal list and
/// the animated list that belongs to [listKey].
///
/// This class only exposes as much of the Dart List API as is needed by the
/// sample app. More list methods are easily added, however methods that
/// mutate the list must make the same changes to the animated list in terms
/// of [AnimatedListState.insertItem] and [AnimatedList.removeItem].
class ListModel<E> {
  ListModel({
    required this.listKey,
    required this.removedItemBuilder,
    Iterable<E>? initialItems,
  }) : _items = List<E>.from(initialItems ?? <E>[]);

  final GlobalKey<AnimatedListState> listKey;
  final RemovedItemBuilder<E> removedItemBuilder;
  final List<E> _items;

  AnimatedListState? get _animatedList => listKey.currentState;

  void insert(int index, E item) {
    _items.insert(index, item);
    _animatedList!.insertItem(index);
  }

  E removeAt(int index) {
    final E removedItem = _items.removeAt(index);
    if (removedItem != null) {
      _animatedList!.removeItem(
        index,
        (BuildContext context, Animation<double> animation) {
          return removedItemBuilder(removedItem, context, animation);
        },
      );
    }
    return removedItem;
  }

  int get length => _items.length;

  E operator [](int index) => _items[index];

  int indexOf(E item) => _items.indexOf(item);
}

/// Displays its integer item as 'item N' on a Card whose color is based on
/// the item's value.
///
/// The text is displayed in bright green if [selected] is
/// true. This widget's height is based on the [animation] parameter, it
/// varies from 0 to 128 as the animation varies from 0.0 to 1.0.
class CardItem extends StatelessWidget {
  const CardItem({
    super.key,
    this.onTap,
    this.selected = false,
    required this.animation,
    required this.item,
  }) : assert(item >= 0);

  final Animation<double> animation;
  final VoidCallback? onTap;
  final int item;
  final bool selected;

  @override
  Widget build(BuildContext context) {
    TextStyle textStyle = Theme.of(context).textTheme.headline4!;

    BoxDecoration deco = BoxDecoration();

    // final int my_index = _list.indexWhere(((obj) => obj == item));

    // if (selected) {
    //
    //    deco = BoxDecoration(
    // border: Border.all( //<-- SEE HERE
    // width: 5, color: Color(0xff79d7dd)
    // ),
    // );
    //
    //   textStyle = textStyle.copyWith(color: Colors.lightGreenAccent[400]);
    // }
    return Padding(
      padding: const EdgeInsets.all(2.0),
      child: SizeTransition(
        sizeFactor: animation,
        child: GestureDetector(
          behavior: HitTestBehavior.opaque,
          onTap: onTap,
          child: Container(
            alignment: Alignment.center,
            decoration: deco,
            child: new Image.file(
              globals.fileslist[item],
              fit: BoxFit.cover,
            ),
          ),

          // child: new Image.file(fileslist[item],
          //     fit: BoxFit.cover,
          //   ),

          // child: SizedBox(
          //   height: 80.0,
          //   child: Card(
          //     color: Colors.primaries[item % Colors.primaries.length],
          //     child: Center(
          //       child: Text('Item $item', style: textStyle),
          //     ),
          //   ),
          // ),
        ),
      ),
    );
  }
}







// void main() {
//   runApp(const MyApp());
// }
//
// class MyApp extends StatelessWidget {
//   const MyApp({Key? key}) : super(key: key);
//
//   // This widget is the root of your application.
//   @override
//   Widget build(BuildContext context) {
//     return MaterialApp(
//       title: 'Flutter Demo',
//       theme: ThemeData(
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
//       home: const PhotoChoice(title: 'Flutter Demo Home Page'),
//     );
//   }
// }

