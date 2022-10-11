library globals;

import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'package:image_picker/image_picker.dart';
import 'dart:io';

BluetoothDevice? global_server;
var fileslist = List<File>.empty(growable: true);
var list_of_int_images = List<List<int>>.empty(growable: true);
