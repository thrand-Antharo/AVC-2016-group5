int line() {
  int num = -160; //keeps track of column
  int sum;
  int w;
  take_picture();      // take camera shot
    for(num=-160,num <= 160, num++){
      w=get_pixel(120, num, 3);
      sum = sum + num*w
    }
      update_screen();
      return sum;
}
