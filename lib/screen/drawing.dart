// ignore_for_file: prefer_const_constructors, camel_case_types

import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:work_kids/screen/addfile.dart';

import 'homeworkaddfile.dart';

class drawing extends StatelessWidget {
  const drawing({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Color(0xfffdefbb),
      appBar: AppBar(
        elevation: 0.0,
        leading: IconButton(
            onPressed: () {
              Navigator.push(context, MaterialPageRoute(builder: (context) {
                return addfile();
              }));
            },
            icon: Icon(
              Icons.arrow_back_ios_new_rounded,
              color: Color(0xff16c29c),
            )),
        title: Text(
          "Drawing",
          style: GoogleFonts.bubblegumSans(
            color: Color(0xff16c29c),
            fontSize: 28,
          ),
        ),
        centerTitle: true,
        backgroundColor: Colors.white,
      ),
      body: Padding(
        padding: const EdgeInsets.fromLTRB(0, 0, 0, 0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.start,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            Padding(
              padding: const EdgeInsets.fromLTRB(20, 0, 20, 0),
              child: Row(
                children: [
                  SizedBox(
                    child: IconButton(
                      onPressed: () {},
                      icon: Image.asset("assets/images/delete.png"),
                      iconSize: 100,
                    ),
                  ),
                  SizedBox(
                    child: IconButton(
                      onPressed: () {},
                      icon: Image.asset("assets/images/saveas.png"),
                      iconSize: 100,
                    ),
                  ),
                  SizedBox(
                    child: IconButton(
                      onPressed: () {
                        Navigator.push(context,
                            MaterialPageRoute(builder: (context) {
                          return homeworkaddfile();
                        }));
                      },
                      icon: Image.asset("assets/images/addattachment.png"),
                      iconSize: 100,
                    ),
                  ),
                ],
              ),
            ),
            Padding(
              padding: const EdgeInsets.fromLTRB(280, 0, 10, 0),
              child: Column(children: [
                SizedBox(
                  child: IconButton(
                    onPressed: () {},
                    icon: Image.asset("assets/images/red.png"),
                    iconSize: 60,
                  ),
                ),
                SizedBox(
                  child: IconButton(
                    onPressed: () {},
                    icon: Image.asset("assets/images/yellow.png"),
                    iconSize: 60,
                  ),
                ),
                SizedBox(
                  child: IconButton(
                    onPressed: () {},
                    icon: Image.asset("assets/images/green.png"),
                    iconSize: 60,
                  ),
                ),
                SizedBox(
                  child: IconButton(
                    onPressed: () {},
                    icon: Image.asset("assets/images/blue.png"),
                    iconSize: 60,
                  ),
                ),
                SizedBox(
                  child: ElevatedButton(
                    style: ElevatedButton.styleFrom(
                      primary: Color(0xfff6cdde),
                      shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.all(Radius.circular(20))),
                    ),
                    child: Image.asset(
                      "assets/images/pen.png",
                    ),
                    onPressed: () {},
                  ),
                ),
                SizedBox(
                  child: ElevatedButton(
                    style: ElevatedButton.styleFrom(
                      primary: Color(0xff16c29c),
                      shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.all(Radius.circular(20))),
                    ),
                    child: Image.asset(
                      "assets/images/pencil.png",
                    ),
                    onPressed: () {},
                  ),
                ),
                SizedBox(height: 5),
                SizedBox(
                  child: ElevatedButton(
                    style: ElevatedButton.styleFrom(
                      primary: Color(0xfff55252),
                      shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.all(Radius.circular(20))),
                    ),
                    child: Image.asset(
                      "assets/images/eraser.png",
                    ),
                    onPressed: () {},
                  ),
                ),
              ]),
            )
          ],
        ),
      ),
    );
  }
}
