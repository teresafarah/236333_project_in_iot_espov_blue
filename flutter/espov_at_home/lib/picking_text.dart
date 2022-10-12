import 'package:flutter/material.dart';
import 'package:auto_size_text_field/auto_size_text_field.dart';


class PickingText extends StatelessWidget {
  const PickingText({Key? key}) : super(key: key);
  @override
  Widget build(BuildContext context) {
    return Scaffold(

      body: Center(
        child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.center,
            mainAxisSize: MainAxisSize.min,
            children:  <Widget>[
              MyCustomForm(),

            ]
        ),


      ),
    );
  }
}





class MyCustomForm extends StatelessWidget {
  const MyCustomForm({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: <Widget>[
        const Padding(
          padding: EdgeInsets.symmetric(horizontal: 8, vertical: 16),
          child: TextField(
            decoration: InputDecoration(
              border: OutlineInputBorder(),
              hintText: 'Enter a simple text',
            ),
          ),
        ),

      ],
    );
  }
}



////



class MyHomePage extends StatefulWidget {
  const MyHomePage({Key? key}) : super(key: key);

  @override
  _MyHomePageState createState() => _MyHomePageState();
}



class _MyHomePageState extends State<MyHomePage> {
  TextEditingController? _textEditingControllerFive;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: SingleChildScrollView(
        child: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              SizedBox(height: 150),

              Padding(
                padding: const EdgeInsets.symmetric(vertical: 24.0),
                child: Container(
                  constraints: BoxConstraints(

                    maxHeight: 300,
                    maxWidth: 300,
                    minHeight: 300,
                    minWidth: 300
                  ),
                  decoration: BoxDecoration(
                    border: Border.all(width: 4, color: Color(0xff79d7dd)),
                      borderRadius: BorderRadius.all(Radius.circular(20))

                  ),

                  child: AutoSizeTextField(
                    controller: _textEditingControllerFive,
                    fullwidth: false,
                    minFontSize: 0,
                    maxLines: null,
                    style: TextStyle(fontSize: 50),
                    textAlignVertical: TextAlignVertical.center,
                    decoration: InputDecoration(
                        border: InputBorder.none,
                        isDense: true,
                        contentPadding: const EdgeInsets.all(20)
                    ),
                    keyboardType: TextInputType.multiline,
                  ),
                ),
              ),
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
                  _textEditingControllerFive?.clear();
                },
                child: const Text('   clear   ',style: TextStyle(color: Color(0xFFFFFFFF),),
                ),
              ),
              // TextButton(
              //     onPressed: () {
              //       _textEditingControllerFive?.clear();
              //     },
              //     child: Text('clear'))
            ],
          ),
        ),
      ), // This trailing comma makes auto-formattig nicer for build methods.
    );
  }

  @override
  void initState() {
    super.initState();
    _textEditingControllerFive = TextEditingController();
  }

  @override
  void dispose() {
    _textEditingControllerFive?.dispose();
    super.dispose();
  }
}
