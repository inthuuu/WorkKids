// ignore_for_file: prefer_const_constructors, use_key_in_widget_constructors

import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:work_kids/screen/homework1.dart';

class HomeScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Color(0xfffdefbb),
      appBar: AppBar(
        elevation: 0.0,
        leading: IconButton(
            onPressed: () {}, icon: Image.asset("assets/images/menu.png")),
        title: Image.asset(
          "assets/images/logo.png",
          height: 30,
        ),
        centerTitle: true,
        backgroundColor: Colors.white,
        actions: <Widget>[
          IconButton(
            onPressed: () {},
            icon: Image.asset("assets/images/profile.png"),
          ),
        ],
      ),
      body: Padding(
        padding: const EdgeInsets.fromLTRB(30, 30, 30, 0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.start,
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Padding(
              padding: const EdgeInsets.fromLTRB(0, 10, 0, 0),
              child: SizedBox(
                child: Text(
                  "Today is Monday, 5 June",
                  style: GoogleFonts.bubblegumSans(
                    color: Color(0xffad95f3),
                    fontSize: 24,
                  ),
                ),
              ),
            ),
            Row(
              children: [
                SizedBox(
                  child: IconButton(
                    onPressed: () {
                      Navigator.push(context,
                          MaterialPageRoute(builder: (context) {
                        return homework();
                      }));
                    },
                    icon: Image.asset("assets/images/homework.png"),
                    iconSize: 150,
                  ),
                ),
                SizedBox(
                  height: 30,
                ),
                SizedBox(
                  child: IconButton(
                    onPressed: () {},
                    icon: Image.asset("assets/images/test.png"),
                    iconSize: 150,
                  ),
                ),
              ],
            ),
            SizedBox(child: Image.asset("assets/images/upcoming.png")),
            SizedBox(
              height: 20,
            ),
            SizedBox(
              child: ElevatedButton(
                style: ElevatedButton.styleFrom(
                    primary: Color(0xfff6cdde),
                    shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.all(Radius.circular(20))),
                    elevation: 40),
                child: Padding(
                  padding: const EdgeInsets.all(15),
                  child: Image.asset(
                    "assets/images/mypet.png",
                  ),
                ),
                onPressed: () {},
              ),
            ),
          ],
        ),
      ),
      bottomNavigationBar: BottomNavigationBar(
        items: <BottomNavigationBarItem>[
          BottomNavigationBarItem(
              icon: Image.asset(
                "assets/images/homeicon.png",
                height: 35,
              ),
              label: 'Home'),
          BottomNavigationBarItem(
            icon: Image.asset(
              "assets/images/homeworkicon.png",
              height: 35,
            ),
            label: 'Homework',
          ),
          BottomNavigationBarItem(
            icon: Image.asset(
              "assets/images/classesicon.png",
              height: 35,
            ),
            label: 'Classes',
          ),
          BottomNavigationBarItem(
            icon: Image.asset(
              "assets/images/chaticon.png",
              height: 35,
            ),
            label: 'Chat',
          ),
          BottomNavigationBarItem(
            icon: Image.asset(
              "assets/images/notiicon.png",
              height: 35,
            ),
            label: 'Notification',
          ),
        ],
        unselectedLabelStyle: GoogleFonts.bubblegumSans(
          color: Color(0xffad95f3),
          fontSize: 14,
        ),
        selectedLabelStyle: GoogleFonts.bubblegumSans(
          color: Color(0xffad95f3),
          fontSize: 14,
        ),
        showSelectedLabels: true,
        showUnselectedLabels: true,
        unselectedItemColor: Color(0xffad95f3),
        selectedItemColor: Color(0xfff55252),
      ),
    );
  }
}
