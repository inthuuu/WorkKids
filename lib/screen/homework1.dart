// ignore_for_file: prefer_const_constructors, camel_case_types

import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:work_kids/screen/addfile.dart';
import 'package:work_kids/screen/home.dart';
import 'package:work_kids/screen/homeworkdone.dart';

class homework extends StatelessWidget {
  OverlayEntry? entry;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Color(0xfffdefbb),
      appBar: AppBar(
        elevation: 0.0,
        leading: IconButton(
            onPressed: () {
              Navigator.push(context, MaterialPageRoute(builder: (context) {
                return HomeScreen();
              }));
            },
            icon: Icon(
              Icons.arrow_back_ios_new_rounded,
              color: Color(0xffad95f3),
            )),
        title: Text(
          "Homework1",
          style: GoogleFonts.bubblegumSans(
            color: Color(0xffad95f3),
            fontSize: 28,
          ),
        ),
        centerTitle: true,
        backgroundColor: Colors.white,
      ),
      body: Padding(
        padding: const EdgeInsets.fromLTRB(30, 30, 30, 0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.start,
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            SizedBox(
                child: Text(
              "Homework1",
              style: GoogleFonts.bubblegumSans(
                color: Color(0xffad95f3),
                fontSize: 24,
              ),
            )),
            SizedBox(
                child: Text(
              "Due date 9.08.2021 12.00 p.m",
              style: GoogleFonts.bubblegumSans(
                color: Color(0xff706d67),
                fontSize: 16,
              ),
            )),
            SizedBox(height: 20),
            SizedBox(child: Image.asset("assets/images/line.png")),
            SizedBox(height: 20),
            SizedBox(
                child: Text(
              "Description",
              style: GoogleFonts.bubblegumSans(
                color: Color(0xff0fbf99),
                fontSize: 16,
              ),
            )),
            SizedBox(height: 10),
            SizedBox(
                child: Text(
              "Do homework 1, 2, 3 on page 18",
              style: GoogleFonts.bubblegumSans(
                color: Colors.black,
                fontSize: 18,
              ),
            )),
            SizedBox(height: 30),
            SizedBox(
                child: Text(
              "file attached",
              style: GoogleFonts.bubblegumSans(
                color: Color(0xff0fbf99),
                fontSize: 16,
              ),
            )),
            SizedBox(height: 10),
            SizedBox(
              height: 50,
              width: double.infinity,
              child: OutlinedButton(
                style: ElevatedButton.styleFrom(
                    primary: Colors.white,
                    shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.all(Radius.circular(10)))),
                child: Padding(
                  padding: const EdgeInsets.all(8.0),
                  child: Row(
                    children: [
                      Image.asset("assets/images/pdf.png"),
                      Text(
                        "   homework1.pdf",
                        style: TextStyle(fontSize: 14, color: Colors.black),
                      )
                    ],
                  ),
                ),
                onPressed: () {},
              ),
            ),
            SizedBox(height: 35),
            SizedBox(
                child: Text(
              "Your Homework",
              style: GoogleFonts.bubblegumSans(
                color: Color(0xffad95f3),
                fontSize: 24,
              ),
            )),
            SizedBox(
                child: Text(
              "You can attach your homework here",
              style: GoogleFonts.bubblegumSans(
                color: Color(0xff706d67),
                fontSize: 16,
              ),
            )),
            SizedBox(height: 20),
            SizedBox(
              height: 60,
              width: double.infinity,
              child: OutlinedButton(
                style: ElevatedButton.styleFrom(
                    primary: Colors.white,
                    shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.all(Radius.circular(10)))),
                child: Padding(
                  padding: const EdgeInsets.all(8.0),
                  child: Row(
                    crossAxisAlignment: CrossAxisAlignment.center,
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Image.asset("assets/images/addfileicon.png"),
                      Text(
                        "   Add Attachment",
                        style: GoogleFonts.bubblegumSans(
                          color: Color(0xff706d67),
                          fontSize: 16,
                        ),
                      )
                    ],
                  ),
                ),
                onPressed: () {
                  Navigator.push(context, MaterialPageRoute(builder: (context) {
                    return addfile();
                  }));
                },
              ),
            ),
            SizedBox(height: 20),
            SizedBox(
              height: 60,
              width: double.infinity,
              child: ElevatedButton(
                style: ElevatedButton.styleFrom(
                    primary: Color(0xffad95f3),
                    shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.all(Radius.circular(10)))),
                child: Text(
                  "Turn in",
                  style: GoogleFonts.bubblegumSans(
                    color: Colors.white,
                    fontSize: 24,
                  ),
                ),
                onPressed: () {
                  entry = OverlayEntry(
                      builder: (context) => Positioned(
                            top: 350,
                            left: 100,
                            child: ElevatedButton(
                              onPressed: () {
                                Navigator.push(context,
                                    MaterialPageRoute(builder: (context) {
                                  return homeworkdone();
                                }));
                                entry?.remove();
                                entry = null;
                              },
                              style: ElevatedButton.styleFrom(
                                primary: Color(0xff92caff),
                                shape: RoundedRectangleBorder(
                                    borderRadius:
                                        BorderRadius.all(Radius.circular(10))),
                                elevation: 40,
                              ),
                              child: Padding(
                                padding: const EdgeInsets.all(8.0),
                                child: Column(
                                  children: [
                                    Image.asset(
                                      "assets/images/coin.png",
                                      height: 80,
                                    ),
                                    Text(
                                      "Receive 5 coins",
                                      style: GoogleFonts.bubblegumSans(
                                        color: Colors.white,
                                        fontSize: 24,
                                      ),
                                    ),
                                  ],
                                ),
                              ),
                            ),
                          ));
                  final overlay = Overlay.of(context)!;
                  overlay.insert(entry!);
                },
              ),
            ),
            SizedBox(height: 45),
            SizedBox(child: Image.asset("assets/images/footimage.png"))
          ],
        ),
      ),
    );
  }
}
