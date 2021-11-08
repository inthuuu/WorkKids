// ignore_for_file: prefer_const_constructors, camel_case_types

import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';

import 'addfile.dart';
import 'homeworkaddfile.dart';

class note extends StatelessWidget {
  const note({Key? key}) : super(key: key);

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
              color: Color(0xffffc350),
            )),
        title: Text(
          "Take a note",
          style: GoogleFonts.bubblegumSans(
            color: Color(0xffffc350),
            fontSize: 28,
          ),
        ),
        centerTitle: true,
        backgroundColor: Colors.white,
      ),
      body: Padding(
        padding: const EdgeInsets.fromLTRB(0, 0, 0, 0),
        child: SingleChildScrollView(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.start,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              Padding(
                padding: const EdgeInsets.fromLTRB(130, 0, 20, 0),
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
                padding: const EdgeInsets.fromLTRB(30, 0, 30, 0),
                child: TextFormField(
                  style: TextStyle(
                    fontSize: 16,
                    color: Colors.black,
                  ),
                  decoration: InputDecoration(
                    hintText: 'Add Title...',
                    hintStyle:
                        TextStyle(fontSize: 16, color: Color(0xFFbdc6cf)),
                    fillColor: Colors.white,
                    filled: true,
                    border: OutlineInputBorder(),
                    enabledBorder: OutlineInputBorder(
                      borderSide:
                          BorderSide(color: Color(0xffdacefc), width: 1.0),
                      borderRadius: BorderRadius.all(Radius.circular(15.0)),
                    ),
                    focusedBorder: OutlineInputBorder(
                      borderSide:
                          BorderSide(color: Color(0xffdacefc), width: 1.5),
                      borderRadius: BorderRadius.all(Radius.circular(15.0)),
                    ),
                  ),
                ),
              ),
              Padding(
                padding: const EdgeInsets.fromLTRB(30, 20, 30, 0),
                child: TextFormField(
                  keyboardType: TextInputType.multiline,
                  maxLines: 15,
                  style: TextStyle(
                    fontSize: 16,
                    color: Colors.black,
                  ),
                  decoration: InputDecoration(
                    hintText: 'Add Title...',
                    hintStyle:
                        TextStyle(fontSize: 16, color: Color(0xFFbdc6cf)),
                    fillColor: Colors.white,
                    filled: true,
                    border: OutlineInputBorder(),
                    enabledBorder: OutlineInputBorder(
                      borderSide:
                          BorderSide(color: Color(0xffdacefc), width: 1.0),
                      borderRadius: BorderRadius.all(Radius.circular(15.0)),
                    ),
                    focusedBorder: OutlineInputBorder(
                      borderSide:
                          BorderSide(color: Color(0xffdacefc), width: 1.5),
                      borderRadius: BorderRadius.all(Radius.circular(15.0)),
                    ),
                  ),
                ),
              ),
              SizedBox(height: 30),
              SizedBox(child: Image.asset("assets/images/footimage.png"))
            ],
          ),
        ),
      ),
    );
  }
}
