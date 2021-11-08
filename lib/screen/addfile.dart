// ignore_for_file: prefer_const_constructors, camel_case_types

import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:work_kids/screen/drawing.dart';
import 'package:work_kids/screen/homework1.dart';
import 'package:work_kids/screen/note.dart';

class addfile extends StatelessWidget {
  const addfile({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Color(0xfffdefbb),
      appBar: AppBar(
        elevation: 0.0,
        title: Text(
          "Add Attachment",
          style: GoogleFonts.bubblegumSans(
            color: Color(0xffad95f3),
            fontSize: 28,
          ),
        ),
        centerTitle: true,
        actions: <Widget>[
          IconButton(
            onPressed: () {
              Navigator.push(context, MaterialPageRoute(builder: (context) {
                return homework();
              }));
            },
            icon: Image.asset("assets/images/closeicon.png"),
          ),
        ],
        backgroundColor: Colors.white,
      ),
      body: Padding(
        padding: const EdgeInsets.fromLTRB(0, 30, 0, 0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.start,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            Padding(
              padding: const EdgeInsets.fromLTRB(30, 0, 30, 0),
              child: Row(
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  SizedBox(
                    child: IconButton(
                      onPressed: () {},
                      icon: Image.asset("assets/images/photo.png"),
                      iconSize: 150,
                    ),
                  ),
                  SizedBox(
                    height: 30,
                  ),
                  SizedBox(
                    child: IconButton(
                      onPressed: () {},
                      icon: Image.asset("assets/images/chooseimage.png"),
                      iconSize: 150,
                    ),
                  ),
                ],
              ),
            ),
            Padding(
              padding: const EdgeInsets.fromLTRB(30, 0, 30, 0),
              child: Row(
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  SizedBox(
                    child: IconButton(
                      onPressed: () {
                        Navigator.push(context,
                            MaterialPageRoute(builder: (context) {
                          return drawing();
                        }));
                      },
                      icon: Image.asset("assets/images/drawing.png"),
                      iconSize: 150,
                    ),
                  ),
                  SizedBox(
                    height: 30,
                  ),
                  SizedBox(
                    child: IconButton(
                      onPressed: () {
                        Navigator.push(context,
                            MaterialPageRoute(builder: (context) {
                          return note();
                        }));
                      },
                      icon: Image.asset("assets/images/note.png"),
                      iconSize: 150,
                    ),
                  ),
                ],
              ),
            ),
            Padding(
              padding: const EdgeInsets.fromLTRB(30, 0, 30, 0),
              child: Row(
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  SizedBox(
                    child: IconButton(
                      onPressed: () {},
                      icon: Image.asset("assets/images/upload.png"),
                      iconSize: 150,
                    ),
                  ),
                ],
              ),
            ),
            SizedBox(
                child: Image.asset(
              "assets/images/footimage2.png",
              height: 130,
            )),
          ],
        ),
      ),
    );
  }
}
