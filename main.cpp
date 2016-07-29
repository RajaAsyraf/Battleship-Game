/******************************************** 
Course : TCP1101 Programming Fundamentals
Session: Trimester 1, 2013/14
Name : Adri Aiman Bin Md Anuar Musaddad
ID   : 1112703527
Name : Raja Mohamad Asyraf Bin Raja Abdul Rahman
ID   : 1112703432
Lecture Section : TC102 
Tutorial Section: TC203 
Project: 02
Email: rmasyraf@gmail.com
Phone: 0177339914
********************************************/
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <iostream>
#include <string>
#include <SFML/Network.hpp>
#define DEBUG false
#include <sstream>  // for ostringstream

using namespace std;


sf::RectangleShape createRectangle(float width = 1.0f, float height = 1.0f, sf::Vector2f position = sf::Vector2f(0,0),
                             const sf::Color& myFillColor = sf::Color::White,
                             const sf::Color& myOutlineColor = sf::Color::Black,
                             float myOutlineThickness = -2
							 )
 {
	sf::RectangleShape myRectangle;
	sf::Vector2f myRectangleSize(width, height);
	myRectangle.setSize(myRectangleSize);
	myRectangle.setPosition(position);
	myRectangle.setFillColor(myFillColor);
	myRectangle.setOutlineColor(myOutlineColor);
	myRectangle.setOutlineThickness(myOutlineThickness);
	return myRectangle;
 }

sf::Font loadFont(const string& fontFilename = "resources/Individigital Demibold.ttf")
{
  sf::Font myFont;
  if (!myFont.loadFromFile(fontFilename))
  {
    cout << "Can not load font from " << fontFilename << endl;
    exit(1);
  }
  return myFont;
}

sf::Font loadFont2(const string& fontFilename = "resources/Individigital Demibold.ttf")
{
  sf::Font myFont;
  if (!myFont.loadFromFile(fontFilename))
  {
    cout << "Can not load font from " << fontFilename << endl;
    exit(1);
  }
  return myFont;
}

sf::Font loadFont3(const string& fontFilename = "resources/Individigital Demibold.ttf")
{
  sf::Font myFont;
  if (!myFont.loadFromFile(fontFilename))
  {
    cout << "Can not load font from " << fontFilename << endl;
    exit(1);
  }
  return myFont;
}

sf::Font loadFont4(const string& fontFilename = "resources/Individigital Demibold.ttf")
{
  sf::Font myFont;
  if (!myFont.loadFromFile(fontFilename))
  {
    cout << "Can not load font from " << fontFilename << endl;
    exit(1);
  }
  return myFont;
}

sf::Font loadFont5(const string& fontFilename = "resources/Individigital Demibold.ttf")
{
  sf::Font myFont;
  if (!myFont.loadFromFile(fontFilename))
  {
    cout << "Can not load font from " << fontFilename << endl;
    exit(1);
  }
  return myFont;
}

class Ship
{
 public:
  Ship(int length=4, int typeNo=1, bool isHorizontal=true, float boxSize=40)
  : length_(length), typeNo_(typeNo),
    isHorizontal_(isHorizontal), boxSize_(boxSize)
  {
	  setLength(length);
    rectangle_.setOrigin(0.0f, 0.0f);
    setColor( sf::Color::Blue, sf::Color::Red);
  }
	void setLength(int length)
	{
	length_ = length;
    width_ = boxSize_ * length_;
    height_ = boxSize_;
    sf::Vector2f rectangleSize(width_, height_);
    rectangle_.setSize(rectangleSize);
    if (!isHorizontal_) changeOrientation();
	}
  int getLength() { return length_; }
	int getTypeNo() { return typeNo_; }
  void setColor(const sf::Color& fillColor,
                const sf::Color& outlineColor,
                float outlineThickness = -2.0f
                )
  {
    fillColor_ = fillColor;
    outlineColor_ = outlineColor;
    outlineThickness_ = outlineThickness;
    rectangle_.setFillColor(fillColor_);
    rectangle_.setOutlineColor(outlineColor_);
    rectangle_.setOutlineThickness(outlineThickness_);
  }
  void changeOrientation()
  {
    isHorizontal_ = !isHorizontal_;
    int temp = width_; width_ = height_; height_ = temp;
    sf::Vector2f rectangleSize(width_, height_);
    rectangle_.setSize(rectangleSize);
  }
  bool isHorizontal()
  {
    return isHorizontal_;
  }
	void setHorizontal()
	{
	  if (isHorizontal_) return;
		changeOrientation();
	}
	void setVertical()
	{
	  if (!isHorizontal_) return;
		changeOrientation();
	}
  void setPosition(int x, int y)
  {
    x_ = x;
    y_ = y;
    //cout << x << " " << y << endl;
    rectangle_.setPosition(x,y);
  }
  void setOrigin(int x, int y)
  {
    rectangle_.setOrigin(x,y);
  }
  void setTypeNo(int typeNo) { typeNo_ = typeNo; }
  void draw(sf::RenderWindow& window)
  {
    window.draw(rectangle_);
  }
  bool hit(int x, int y)
  {
    if (    x > x_ && x < x_+width_
         && y > y_ && y < y_+height_ )
      return true;
    return false;
  }
  int getX() { return x_; }
  int getY() { return y_; }
 private:
  int length_, typeNo_, width_, height_;
  int boxSize_;
  int x_, y_;
  bool isHorizontal_;
  sf::Color fillColor_;
  sf::Color outlineColor_;
  float outlineThickness_;
  sf::RectangleShape rectangle_;
};

class Sea
{
	public:
	 Sea(int OriginX = 50, int OriginY = 100)
	 : gridDimX_(10), gridDimY_(10),  // no of cells for each dimension of the grid
	   cellDimX_(40), cellDimY_(40), // no of pixel for each dimension of the cells
	   OriginX_(OriginX), OriginY_(OriginY),
	   width_(gridDimX_*cellDimX_), height_(gridDimY_*cellDimY_)
	 {
		grid.resize(gridDimY_); // create dimy_ rows
		for (int i = 0; i < gridDimY_; ++i) // for each row
		{
			grid[i].resize(gridDimX_); // create row with dimx_ columns
		}
		for (int i = 0; i < gridDimY_; ++i)
		{
			for (int j = 0; j < gridDimX_; ++j)
			{
				grid[i][j] = 0;
			}
		}
		sf::Vector2f size(cellDimX_, cellDimY_);
		aRectangle_.setSize(size);
		aRectangle_.setFillColor(sf::Color::White);
		aRectangle_.setOutlineColor(sf::Color(000,000,000));
		aRectangle_.setOutlineThickness(-2);
		aRectangle_.setOrigin(0.0f, 0.0f); //origin is at left top corner
	}
	int getOriginX() { return OriginX_; }
	int getOriginY() { return OriginY_; }
	void set(int cellIndexX, int cellIndexY, int type)
	{
		grid[cellIndexY][cellIndexX] = type;
	}
	bool dropShip(int x, int y, Ship& ship)
	{
		int length       = ship.getLength();
		int isHorizontal = ship.isHorizontal();
		int type = ship.getTypeNo();
		//note: x and y are pixel coords relative to window
    if (    x < OriginX_ || x > OriginX_ + width_
         || y < OriginY_ || y > OriginY_ + height_)
      return false;
    int cellIndexX = (x - OriginX_) / cellDimX_;
    int cellIndexY = (y - OriginY_) / cellDimY_;
		int newx = cellIndexX*cellDimX_ + OriginX_;
		int newy = cellIndexY*cellDimY_ + OriginY_;

	bool success = true;
    if (isHorizontal && cellIndexX + length <= gridDimX_)
    {
      bool empty = true;
      for (int j=cellIndexX; j<cellIndexX+length; ++j)
      {
        if (grid[cellIndexY][j] != 0)
        { empty = false; break; }
      }
      if (empty)
      {
        for (int j=cellIndexX; j<cellIndexX+length; ++j)
          grid[cellIndexY][j] = type;

				ship.setPosition(newx, newy);
      }
		success = success && empty;
    }
    if (!isHorizontal && cellIndexY + length <= gridDimY_)
    {
      bool empty = true;
      for (int i=cellIndexY; i<cellIndexY+length; ++i)
      {
        if (grid[i][cellIndexX] != 0)
        { empty = false; break; }
      }
      if (empty)
      {
        for (int i=cellIndexY; i<cellIndexY+length; ++i)
          grid[i][cellIndexX] = type;
				ship.setPosition(newx, newy);
      }
		success = success && empty;
    }
	return success;
  }
  void draw(sf::RenderWindow& window)
  {
    for (int i=0, y=OriginY_; i<gridDimY_; ++i, y+=cellDimY_)
    {
      for (int j=0, x=OriginX_; j<gridDimX_; ++j, x+=cellDimX_)
      {
        aRectangle_.setPosition(x,y);
        if (grid[i][j] == 0)
        {
          aRectangle_.setFillColor(sf::Color::Blue);
        }
        else if (grid[i][j] == 1)
        {
          aRectangle_.setFillColor(sf::Color::Yellow);
        }
		// else if ( grid[i][j] == 3 )
		// {
			 // aRectangle_.setOutlineColor(sf::Color::Red);
		// }
		// else if ( grid[i][j] == 4 )
		// {
			 // aRectangle_.setOutlineColor(sf::Color::White);
		// }
        window.draw(aRectangle_);
      }
    }
  }
  int hit(int r, int c)
  {
	return grid[r][c];
  }

  public:
  const int gridDimX_, gridDimY_;
  vector < vector<int> > grid; //2D array of int
  const int cellDimX_, cellDimY_;
  int OriginX_, OriginY_, width_, height_;
  sf::RectangleShape aRectangle_;
};


class MyHost
{
 public:
  MyHost(unsigned short port = 50001)
  : myPort(port)
  {
    mySocket.setBlocking(false);
  }
  sf::Socket::Status initiateAsServer();
  sf::Socket::Status connectToServer(sf::IpAddress server);
  sf::Socket::Status sendMessage(string outMsg);
  sf::Socket::Status receiveMessage(string& inMsg);
 private:
  unsigned short myPort;
  sf::TcpSocket mySocket;
};

sf::Socket::Status MyHost::initiateAsServer()
{
  // Create a server socket to accept new connections
  sf::TcpListener listener;
  sf::Socket::Status status;

  // Listen to the given port for incoming connections
  status = listener.listen(myPort);
  if (status != sf::Socket::Done)
  {
    if (DEBUG) cout << "initiateAsServer(): Listen Failed!" << endl;
    if (DEBUG) cout << status << endl;
    return status;
  }
  if (DEBUG) cout << "Server is listening to port " << myPort << ", waiting for connections... " << endl;

  // Wait for a connection
  status = listener.accept(mySocket);
  if (status != sf::Socket::Done)
  {
    if (DEBUG) cout << "initiateAsServer(): Accept Failed!" << endl;
    if (DEBUG) cout << status << endl;
    return status;
  }
  if (DEBUG) cout << "Client connected: " << mySocket.getRemoteAddress() << endl;
  if (DEBUG) cout << status << endl;
  return status;
}

sf::Socket::Status MyHost::connectToServer(sf::IpAddress server)
{
  sf::Socket::Status status;

  // Connect to the server
  status = mySocket.connect(server, myPort);
  if (status != sf::Socket::Done)
  {
    if (DEBUG) cout << "connectToServer(): Connect Failed!" << endl;
    if (DEBUG) cout << status << endl;
    return status;
  }
  if (DEBUG) cout << "Connected to server " << server << endl;
  if (DEBUG) cout << status << endl;
  return status;
}

sf::Socket::Status MyHost::sendMessage(string outMsg)
{
  sf::Socket::Status status;

  // Send a message to the connected client
  status = mySocket.send(outMsg.c_str(), outMsg.length());
  if (status != sf::Socket::Done)
  {
    if (DEBUG) cout << "sendMessage(): Send Failed!" << endl;
    if (DEBUG) cout << status << endl;
    return status;
  }
  //cout << "Message [" << outMsg << "] sent." << endl;
  if (DEBUG) cout << status << endl;
  return status;
}

sf::Socket::Status MyHost::receiveMessage(string& inMsg)
{
  sf::Socket::Status status;

  // Receive a message back from the client
  char in[128];
  size_t sizeReceived;
  status = mySocket.receive(in, sizeof(in), sizeReceived);
  if (status != sf::Socket::Done)
  {
    if (DEBUG) cout << "receiveMessage(): Receive Failed!" << endl;
    if (DEBUG) cout << status << endl;
    return status;
  }
  inMsg = in;
  inMsg = inMsg.substr(0,sizeReceived);
  //cout << "Message [" << inMsg << "] received." << endl;
  if (DEBUG) cout << status << endl;
  return status;
}

sf::SoundBuffer loadSoundBuffer(const string& waveFilename)
{
  sf::SoundBuffer mySoundBuffer;
  if (!mySoundBuffer.loadFromFile(waveFilename))
  {
    cout << "Can not load sound from " << waveFilename << endl;
    exit(1);
  }
  return mySoundBuffer;
}

sf::Sound createSound(const sf::SoundBuffer& mySoundBuffer)
{
  sf::Sound mySound(mySoundBuffer);
  return mySound;
}

int main()
{
	system("cls");

	// ---- Network Connection ----
	bool hostTypeValid;
	char hostType;
	sf::Socket::Status status;
	do{
		cout<<"Enter s for server "<<endl;
		cout<<"Enter c for client "<<endl;
		cout<<" -> ";
		cin>>hostType;

		if( hostType == 's' || hostType == 'S' || hostType == 'c' || hostType == 'C' )
			hostTypeValid = true;
		else
		{
			cout<<"Please enter the correct input"<<endl;
			hostTypeValid = false;
		}
	}while( hostTypeValid == false );

	MyHost host;
	sf::Socket::Status hostStatus;
	if( hostType == 's' || hostType == 'S' )
	{
		cout<<"Turning ON server"<<endl;
		cout<<"Waiting for another user to connect..."<<endl;
		hostStatus = host.initiateAsServer();
		if( hostStatus == sf::Socket::Done )
			cout<<"USER CONNECTED..."<<endl;
	}

	else if( hostType == 'c' || hostType == 'C' )
	{
		string serverString;
		sf::IpAddress iPaddress;
		do{
			cout<<"Enter server IP address -> ";
			cin>>serverString;
			iPaddress = sf::IpAddress(serverString);
		}while(iPaddress == sf::IpAddress::None);

		cout<<"Connecting to server..."<<endl;
		do{
			hostStatus = host.connectToServer(iPaddress);
		}while( hostStatus != sf::Socket::Done );

		cout<<"You have connect to the server"<<endl;
		cout<<"HAVE FUN!"<<endl;
	}
	// End of ---- Network Connection ----

	// My Window
	cout<<"Enjoy Your Game!!";
	const int myWindowWidth = 1200;
	const int myWindowHeight = 800;

	sf::Texture texture;
	if (!texture.loadFromFile("resources/ship.jpg"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);

	const int gridSize = 10;
	int gridCellSize = 50;

	// grid position in X and Y
	int gridX = 650;
	int gridY = 100;

	sf::RectangleShape grid[gridSize][gridSize];

	sf::RectangleShape highlightCell = createRectangle(gridCellSize,gridCellSize); // used for grid cell highlight if mouse is inside a grid cell
	highlightCell.setFillColor(sf::Color(0,255,0, 128));
	highlightCell.setOutlineColor(sf::Color(0,102,0));

	for(int i = 0; i < gridSize; i++) // row
	{
		for(int j = 0; j < gridSize; j++) // column
		{
			grid[i][j] = createRectangle(gridCellSize,gridCellSize, sf::Vector2f(gridX, gridY));
			gridX += gridCellSize; // shift the horizontal position by gridCellSize for next member's position
		} // finish 1 row

		gridY += gridCellSize; // shift the horizontal position by gridCellSize for next row
		gridX = 650; // reset the horizontal position
	}

	gridX = 650;
	gridY = 100;

	Sea sea;

		const int NumOfShips = 4;
		int myShipLength[] = { 3, 3, 2, 2 };
		Ship ship[NumOfShips];

		for(int i = 0; i < NumOfShips; ++i)
		{
			ship[i].setLength(myShipLength[i]);
			//ship[i].setTypeNo(i+1);
		}

		ship[0].setPosition(528, 230);
		ship[1].setPosition(528, 290);
		ship[2].setPosition(465, 270);
		ship[3].setPosition(528, 350);
			ship[2].setVertical();

			int currentShipNo = -1;


		// text
		sf::Font myFont = loadFont();
		sf::Font myFont2 = loadFont2();
		sf::Font myFont3 = loadFont3();
		sf::Font myFont4 = loadFont4();
		sf::Font myFont5 = loadFont5();
		sf::Text myText;
		sf::Text myText2;
		sf::Text myText3;
		sf::Text myText4;
		sf::Text myText5;
		myText.setFont(myFont);
		myText.setCharacterSize(20);
		myText.setColor(sf::Color::White);
		myText2.setFont(myFont2);
		myText2.setCharacterSize(25);
		myText2.setColor(sf::Color::Yellow);
		myText3.setFont(myFont3);
		myText3.setCharacterSize(30);
		myText3.setColor(sf::Color::White);
		myText4.setFont(myFont4);
		myText4.setCharacterSize(40);
		myText4.setColor(sf::Color::Yellow);
		myText5.setFont(myFont5);
		myText5.setCharacterSize(60);
		myText5.setColor(sf::Color::White);

		// sound
		sf::SoundBuffer myBombardBuffer = loadSoundBuffer("resources/explosion-01.wav");
		sf::Sound myBombardSound = createSound(myBombardBuffer);
		sf::SoundBuffer myMissedSoundBuffer = loadSoundBuffer("resources/fail-buzzer-04.wav");
		sf::Sound myMissedSound = createSound(myMissedSoundBuffer);

		// Create Window
		sf::RenderWindow myWindow(sf::VideoMode(myWindowWidth, myWindowHeight, 32), "The BattleShip Project");
		myWindow.setVerticalSyncEnabled(true);

		bool showHardwareMouse;
		bool started;
		bool drag;
		float dragOffsetX, dragOffsetY;
		bool LeftMouseButtonDown = false;
		bool reset = true;
		int countdragged = 0;
		int r = -1, c = -1;
		bool Attacker = false;
		bool Defender = false;
		stringstream ss;
		bool sendOk = false;
		int myShip2_ = 0;
		int myShip = 0;
		int PointTOWIN = 0;
		int PointTOLOSE = 0;
		int x, y;

		if (hostType == 's' || hostType == 'S')  Attacker = true;
		else            						 Defender = true;


		// Main Loop Start HERE!!!
		while (myWindow.isOpen())
		{
			if ( reset)
			{
				// Reset
				showHardwareMouse = true;
				drag = false;
				dragOffsetX = dragOffsetY = 0.0f;
				started = true;
				reset = false;

			}

			// Begin Poll Events
			// Handle Events
			sf::Event myEvent;
			while (myWindow.pollEvent(myEvent))
			{
				if(started)
				{
					switch (myEvent.type)
					{
						case sf::Event::Closed:
						{
							myWindow.close();
							break;
						}

						case sf::Event::KeyPressed:
						{
							switch (myEvent.key.code)
							{
								case sf::Keyboard::Escape:  // When ESC Key been Pressed
								{
									myWindow.close();
									break;
								}

								case sf::Keyboard::Space:  // When SPACE KEy been Pressed
								{
									if (started){
										started = false;
										reset = true;
									}
									else{
										started = true;
										reset = false;
									}
									break;
								}

								case sf::Keyboard::F1:  // When F1 Key been pressed
								{
									showHardwareMouse = !showHardwareMouse;
									myWindow.setMouseCursorVisible(showHardwareMouse);
									break;
								}

								case sf::Keyboard::Left:  // When LEFT ARROW Key been pressed
								case sf::Keyboard::Right:  // When RIGHT ARRPW Key been pressed
								{
									break;
								}
							}
						break;
					} // End of "case" Key Press

					case sf::Event::MouseButtonPressed:
					{
						switch (myEvent.mouseButton.button)
						{
							case sf::Mouse::Left:
							{
								float x = myEvent.mouseButton.x;
								float y = myEvent.mouseButton.y;
									if (!drag)
									{
										for (int i = 0; i < NumOfShips; ++i)
										{
											if (ship[i].hit(x, y))
											{
												currentShipNo = i;
												break;
											}
										}
										if (currentShipNo != -1)
										{
											dragOffsetX = x - ship[currentShipNo].getX();
											dragOffsetY = y - ship[currentShipNo].getY();
											ship[currentShipNo].setOrigin(dragOffsetX, dragOffsetY);
											ship[currentShipNo].setPosition(x, y);
											drag = true;
										}
									} // End of if(!drag)
									if (Attacker){
									//if( x >= 650 && x <= 1150 && y >= 50 && y <= 550){
										r = ((y - gridY) / gridCellSize);
										c = (x - gridX) / gridCellSize;
										ss.str(""); ss.clear();
										ss << r << " " << c;
										 //y = r; x = c;
										// cout<< ss.str();
									//}
									}
							 break;
							}

							case sf::Mouse::Right:
							  {
								  if (currentShipNo != -1)
								  ship[currentShipNo].changeOrientation();
								break;
							  }

						}
						break;
					} // End of Mouse Pressed

					case sf::Event::MouseMoved:
					{
						if (drag)
						{
							sf::Vector2i windowPos = sf::Mouse::getPosition(myWindow);
							ship[currentShipNo].setPosition(windowPos.x, windowPos.y);
						}
						break;
					} // End of Mouse Move

					case sf::Event::MouseButtonReleased:
					{
						switch (myEvent.mouseButton.button)
						{
							case sf::Mouse::Left:
							{
								float x = myEvent.mouseButton.x;
								float y = myEvent.mouseButton.y;
								if (drag)
								{
									ship[currentShipNo].setOrigin(0, 0);
									float newx = x - dragOffsetX;
									float newy = y - dragOffsetY;
									ship[currentShipNo].setPosition(newx, newy);

									bool success = sea.dropShip(newx, newy, ship[currentShipNo]);

									if (!success)
									{
										switch(currentShipNo)
										{
											case 0: ship[currentShipNo].setPosition(528, 230); break;
											case 1: ship[currentShipNo].setPosition(528, 290); break;
											case 2: ship[currentShipNo].setPosition(465, 270); break;
											case 3: ship[currentShipNo].setPosition(528, 350); break;
										}
									}
									else
									{
										ship[currentShipNo].setPosition(-1000, -1000);
										countdragged++;
									}

										currentShipNo = -1;
									drag = false;
									//cout<<countdragged;
								}
							break;
							} // End of case Mouse Button Left

						}
					break;
					} // End of case Mouse Button Released
				} //End of Event Type
			} // End of if(started)

		} // End of Poll Event

		if (countdragged == 4){
		if ( Attacker )
		{
				static bool isShow = true;
				if (isShow)
				{
					isShow = false;
				}
				if ( r >= 0 && r <= 9 && c >= 0 && c <= 9)
				{
					if (!sendOk)
					{
						//cout << "Send Attack: " << ss.str() << endl;
						do{
							status = host.sendMessage(ss.str());
						}while ( status != sf::Socket::Done);
						sendOk = true;
					}

					string reply;
					status = host.receiveMessage(reply);
					if ( status == sf::Socket::Done)
					{
						//cout << "Receiving Feedback" << endl;
						ss.str(""); ss.clear();
						ss << reply;

						int shipHit;
						ss >> shipHit;
						//cout << "Feedback = " << shipHit << endl;

						if (shipHit > 0)
						{
							if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
							{
								grid[r][c].setFillColor(sf::Color::Red);
								 myBombardSound.play();
							}
							isShow = true;
							PointTOWIN++;
							//sea.grid[r][c] = 3;
							if (PointTOWIN == 10){
								//cout<<"YOU WON!!!"<<endl;
								isShow = false;
							}
						}
						else
						{
							if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
							{
								grid[r][c].setFillColor(sf::Color::Blue);
								myMissedSound.play();
							}
							//sea.grid[r][c] = 4;
							Attacker = false;
							Defender = true;
						}
						sendOk = false;

						r = -1;
					}
				}

		}
		else if ( Defender )
		{
			static bool isShow = true;
			if (isShow)
			{
				isShow = false;
			}
			string reply;
			status = host.receiveMessage(reply);
			if (status == sf::Socket::Done)
			{
				ss.str(""); ss.clear();
				ss << reply;
				ss >> r >> c;
				//cout << "Attack received" << r << ", " << c << endl;
				 myShip = sea.hit(r, c); // [0, 4]
				 ss.str(""); ss.clear();
				 ss << myShip;
				 myShip2_ = myShip;
				 //cout << "Sending Feedback Attack: " << myShip << endl;
				  do {
					status = host.sendMessage(ss.str());
				} while (status != sf::Socket::Done);
				//cout << "Feedback Sent" << endl;
				//cout<< myShip <<endl;
				if ( myShip > 0){
					isShow = true;
					PointTOLOSE ++;
					if (PointTOLOSE == 10)
					{ 	//cout << "YOU LOSE!!!";
						isShow = false;

					}
					cout<<endl;
					cout<<"Awh! Your ship at ( " << c+1 << " , " << r+1 << " )  has been ATTACKED!!!"<<endl;;
					//int HitColor = -1;
					//sea.SetColor(y , x ,HitColor);
				}
				else
				{
					Attacker = true;
					Defender = false;
				}
				r = -1;
			}
		}
		}

		// Drawing Start here
		myWindow.clear(sf::Color(100, 100, 200));
		myWindow.draw(sprite);

		sf::Vector2i windowPos = sf::Mouse::getPosition(myWindow);
		sf::Vector2i pointerPos = sf::Mouse::getPosition(myWindow);

		ostringstream sout;
		sout<< " ( " << windowPos.x << " , " << windowPos.y << " ) ";
		myText.setString(sout.str());
		myText.setPosition(windowPos.x, windowPos.y);
		myWindow.draw(myText);

		if ( PointTOWIN < 10 && PointTOLOSE < 10){
		myText2.setString("Opponent :");
		myText2.setPosition(480, 80);
		myWindow.draw(myText2);

		myText5.setString("The Battleship Game");
		myText5.setPosition(360, 680);
		myWindow.draw(myText5);


		if ( countdragged == 4){
		for(int i=0; i < gridSize; i++)
			for (int j = 0; j < gridSize; j++)
			{
				myWindow.draw(grid[i][j]); // draw grid cell

				// get grid cell bounds, used to check whether mouse is inside bounds or not
				sf::FloatRect gridBounds = grid[i][j].getGlobalBounds();

				if(gridBounds.contains((sf::Vector2f)pointerPos))
				{
					highlightCell.setPosition(grid[i][j].getPosition()); // set position of highlightCell to be at gridcell
					myWindow.draw(highlightCell); // proceed to draw the highlightCell

					}
				}

			}
		}
		else
		{
			if ( PointTOLOSE == 10){
			myText3.setString("YOU LOSE!");
			myText3.setPosition(800, 200);
			myWindow.draw(myText3);
			}
			else if ( PointTOWIN == 10)
			{
				myText3.setString("CONGRATS! YOU WON!");
				myText3.setPosition(620, 200);
				myWindow.draw(myText3);
			}
		}

		if ( Attacker )
		{
			myText4.setString("Your Turn");
			myText4.setPosition(130, 500);
			myWindow.draw(myText4);
		}
		else if ( Defender )
		{
			myText4.setString("Enemy Turn");
			myText4.setPosition(80, 500);
			myWindow.draw(myText4);
		}

				sea.draw(myWindow);

			for (int i = 0; i < NumOfShips; ++i)
			{
				ship[i].draw(myWindow);
			}

		// Display things on screen
		myWindow.display();

} // End of while (window.isOpen())

return EXIT_SUCCESS;


}
