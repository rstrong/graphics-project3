void menu(int value)
{
    main_keyboard((unsigned char)value, 0, 0);
}

void set_mode(int option)
{
  if(option == 0)
  {
    std::cout << "Mode now set to 0" << std::endl;
    MODE = 0;
    N = 1;
  }
  if(option == 1)
  {
    std::cout << "Mode now set to 1" << std::endl;
    MODE = 1;
  }
  if(option == 2)
  {
    std::cout << "mode now set to 2" << std::endl;
    MODE = 2;
  }
}

void change_n(int option)
{
  if(option == 0)
  {
    std::cout << "N set to 1" << std::endl;
    N = 1;
  }
  if(option == 1)
  {
    std::cout << "N set to 5" << std::endl;
    N = 5;
  }
  if(option == 2)
  {
    std::cout << "N set to 10" << std::endl;
    N = 10;
  }
  if(option == 3)
  {
    std::cout << "N set to 20" << std::endl;
    N = 20;
  }
}

void reset(int option)
{
  if(option == 0)
  {}
  if(option == 1)
  {
    rd.calculate_semistable();
    iter = 0;
  }
}

void change_mode(int option)
{
  if(option == 0)
  {
    rd.init(1,1.0);
    dp1 = 0.04;
    dp2 = 0.06;
    dp3 = 0.04;
    df1 = 0.009;
    df2 = 0.2;
    std::cout << "Type is now stripe" << std::endl;
  }
  if(option == 1)
  {
    rd.init(2,1.0);
    dp1 = 0.8;
    dp2 = 0;
    dp3 = 0;
    df1 = 0.25;
    df2 = 0.0625;
    std::cout << "Type is now spot" << std::endl;
  }
  rd.set_p(dp1,dp2,dp3);
  rd.set_diff(df1,df2);
  rd.calculate_semistable();
}

void predefined(int option)
{
  if(option == 0)
  {
    rd.init(1,1.0);
    dp1 = 0.04;
    dp2 = 0.06;
    dp3 = 0.04;
    df1 = 0.009;
    df2 = 0.2;
    std::cout << "default stripes" << std::endl;
  }
  if(option == 1)
  {
    rd.init(1,1.0);
    dp1 = 0.04;
    dp2 = 0.06;
    dp3 = 0.04;
    df1 = 0.122;
    df2 = 0.2;
    std::cout << "large stripes" << std::endl;
  }
  if(option == 2)
  {
    rd.init(2,1.0);
    dp1 = 0.16;
    dp2 = 0;
    dp3 = 0;
    df1 = 0.25;
    df2 = 0.0625;
    std::cout << "defautl dots" << std::endl;
  }
  rd.set_p(dp1,dp2,dp3);
  rd.set_diff(df1,df2);
  rd.calculate_semistable();
}

void setup_menus(void)
{
  int sub_type = glutCreateMenu(change_mode);
  glutAddMenuEntry("Stripes", 0);
  glutAddMenuEntry("Spots", 1);
  int def = glutCreateMenu(predefined);
  glutAddMenuEntry("Small Stripes", 0);
  glutAddMenuEntry("Large Stripes" , 1);
  glutAddMenuEntry("Small Dots", 2);
  glutAddMenuEntry("Larger Dots", 3);
  int sub_mode = glutCreateMenu(set_mode);
  glutAddMenuEntry("Standard (fast iteration)", 0);
  glutAddMenuEntry("N - Step", 1);
  glutAddMenuEntry("Space Step (slow)", 2);
  int sub_n = glutCreateMenu(change_n);
  glutAddMenuEntry("N = 1", 0);
  glutAddMenuEntry("N = 5" , 1);
  glutAddMenuEntry("N = 10" , 2);
  glutAddMenuEntry("N = 20", 3);
  int sub_reset = glutCreateMenu(reset);
  glutAddMenuEntry("No", 0);
  glutAddMenuEntry("Confirm", 1);
  
  glutCreateMenu(menu);
  glutAddSubMenu("Diffusion Mode", sub_type);
  glutAddSubMenu("Examples", def);
  glutAddSubMenu("Step Mode", sub_mode);
  glutAddSubMenu("N", sub_n);
  glutAddSubMenu("Restart", sub_reset);


  glutAttachMenu(GLUT_RIGHT_BUTTON);
    


}

