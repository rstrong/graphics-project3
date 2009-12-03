void motion(int x, int y)
{
  if(mouse_button == GLUT_LEFT_BUTTON)
  {
    // compute the angle (0..360) around x axis, and y-axis
    y_angle += (float(x - mouse_x)/WIDTH)*360.0;
    x_angle += (float(y - mouse_y)/HEIGHT)*360.0;

  }

  if(mouse_button == GLUT_MIDDLE_BUTTON)
  {
    scale += (y - mouse_y) / 1000.0;
    
    if(scale < 0.001)   scale = 0.001;
    if(scale > 6.0)   scale = 6.0;
    std::cout << "new scale: " << scale << std::endl;
  }

  mouse_x = x;    // update current mouse position
  mouse_y = y;
  redisplay_all();
  std::cout << "x: " << x << " y: " << y << std::endl;
}

void mouse(int button, int state, int x, int y)
{
  // button -- GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON.
  // state  -- GLUT_UP, GLUT_DOWN
  mouse_x = x;
  mouse_y = y;

  mouse_button = button;
  motion(x,y);
}

void main_keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
    case 'a' :
      if(CAMERA_OPTION == 2)
      {
        eye_mag *= 1.1;
        eyex *= 1.1;
        eyey *= 1.1;
        eyez *= 1.1;
      }
      if(CAMERA_OPTION == 3)
      {
        cary += 0.1;
      }
      break;
    case 's' : 
      if(CAMERA_OPTION == 2)
      {
        eye_mag *= 0.9;
        eyex *= 0.9;
        eyey *= 0.9;
        eyez *= 0.9;
      }
      if(CAMERA_OPTION == 3)
      {
        cary -= 0.1;
      }
      break;
    case 'u' :
      eyex += 0.1;
      break;
    case 'U' :
      lookx += 0.1;
      break;
    case 'i' :
      eyex -= 0.1;
      break;
    case 'I' : 
      lookx -= 0.1;
      break;
    case 'j' :
      eyey += 0.1;
      break;
    case 'J' : 
      looky += 0.1;
      break;
    case 'k' :
      eyey -= 0.1;
      break;
    case 'K' :
      looky -= 0.1;
      break;
    case 'n' :
      eyez += 0.1;
      break;
    case 'N' :
      lookz += 0.1;
      break;
    case 'm' :
      eyez -= 0.1;
      break;
    case 'M' : 
      lookz -= 0.1;
      break;
    case 'e' : 
      carx += 1;
      break;
    case 'E' :
      carx -= 1;
      break;
    case 'r' : 
      cary += 1;
      break;
    case 'R' : 
      cary -= 1;
      break;
    case 't':
      carz += 1;
      break;
    case 'T':
      carz -= 1;
      break;
    default:
      break;
  }

  std::cout << "EYEZ: " << eyex << " " << eyey << " " << eyez << " | " << lookx << " " << looky << " " << lookz << std::endl;
  std::cout << "CAR: " << carx << " " << cary << " " << carz << std::endl;
  redisplay_all();
}

void special_keyboard(int key, int x, int y)
{
  switch(key)
  {
  case GLUT_KEY_LEFT:
    if(CAMERA_OPTION == 0 || CAMERA_OPTION == 3)
    {
      car_angle += 5;
    }
    if(CAMERA_OPTION == 1)
    {
      light_angle -= 3;  
    }
    if(CAMERA_OPTION == 2)
    {
      eye_angle -= 3;
    }
    break;
  case GLUT_KEY_RIGHT:
    if(CAMERA_OPTION == 0 || CAMERA_OPTION == 3)
    {
      car_angle -= 5;
    }
    if(CAMERA_OPTION == 1)
    {
      light_angle += 3;
    }
    if(CAMERA_OPTION == 2)
    {
      eye_angle += 3;
    }
    break;
  case GLUT_KEY_UP:
    if(CAMERA_OPTION == 0 || CAMERA_OPTION == 3)
    {
      car_speed += 0.1;
    }
    if(CAMERA_OPTION == 2)
    {
      eyey += 0.1;
    }
    break;
  case GLUT_KEY_DOWN:
    if(CAMERA_OPTION == 0 || CAMERA_OPTION == 3)
    {
      car_speed -= 0.1;
    }
    if(CAMERA_OPTION == 2)
    {
      eyey -= 0.1;
    }
    break;
  default:
    break;
  }
  if(CAMERA_OPTION == 0 || CAMERA_OPTION == 3)
  {
    if(car_angle == 360 || car_angle == -360)
    {
      car_angle = 0;
    }
    steer.setValue((float)(car_speed * cos((-car_angle)*PI/180)), 0.0f, (float)(car_speed * sin((-car_angle)*PI/180)));
    move_car(); 
    std::cout << "New Car Position: " << carx << " " << cary << " " << carz << std::endl;
    std::cout << "EYEZ: " << eyex << " " << eyey << " " << eyez << " | " << lookx << " " << looky << " " << lookz << std::endl;
    //top_display();
  }
  if(CAMERA_OPTION == 1)
  {
    if(light_angle == 360 || light_angle == -360)
    {
      light_angle = 0;
    }
    LightPos[0] = 25*sin((float)light_angle*PI/180);
    LightPos[2] = 25*cos((float)light_angle*PI/180);
    std::cout << "New Light Pos: " << LightPos[0] << " " << LightPos[1] << " " << LightPos[2] << std::endl;
    //top_display();
  }
  if(CAMERA_OPTION == 2)
  {
    if(eye_angle == 360 || eye_angle == -360)
    {
      eye_angle = 0;
    }
    eyex = eye_mag*cos((float)eye_angle*PI/180);
    eyez = eye_mag*sin((float)eye_angle*PI/180);
    std::cout << "New Eyes: " << eyex << " " << eyey << " " << eyez << std::endl;
    //top_display();
  }
  redisplay_all();
}
