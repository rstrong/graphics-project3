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

void setup_menus(void)
{
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
  glutAddSubMenu("Step Mode", sub_mode);
  glutAddSubMenu("N", sub_n);
  glutAddSubMenu("Restart", sub_reset);

  glutAttachMenu(GLUT_RIGHT_BUTTON);
    


}

