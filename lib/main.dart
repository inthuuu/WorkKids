// ignore_for_file: prefer_const_constructors

import 'package:flutter/material.dart';
import 'screen/home.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: "My App",
      theme: ThemeData(primaryColor: Color(0xfffdefbb)),
      home: HomeScreen(),
    );
  }
}
