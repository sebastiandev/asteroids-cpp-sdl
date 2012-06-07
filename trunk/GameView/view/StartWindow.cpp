#include "StartWindow.h"

StartWindow::StartWindow(ClientActionsListener* listener)
{
	controller = listener;
	init();
}

StartWindow::~StartWindow(void)
{
	delete tabPanel;
	delete statusBar;
	delete surface;
	TTF_Quit();
	SDL_Quit();
}

void StartWindow::addScenes(list<string> scenes)
{
	sceneNames = scenes;
	Color* bgColor = new Color(255, 255, 0, 255);
	Color* selectedBgColor = new Color(255, 255, 0);
	SDLLabel* sceneLabel;
	list<string>::iterator it;
	for (it=scenes.begin(); it!=scenes.end(); it++)
	{
		sceneLabel = new SDLLabel(*it, surface);
		sceneLabel->setBackgroundColor(bgColor);
		sceneLabel->setSelectedBackgroundColor(selectedBgColor);
		scenesPanel->addComponent(sceneLabel);
	}
	//TODO: El incremento del scrollbar no se debe definir aqui
	scenesPanel->getScrollBar()->setUnitIncrement(sceneLabel->getHeight());
}

void StartWindow::show(void)
{
	handleEvents();
}

string StartWindow::getSelectedShipName(void)
{
	string shipName = "nave1";
	SDLToggleButton* button;
	if (shipsButtonPanel->isButtonSelected())
	{
		button = shipsButtonPanel->findSelectedButton();
		shipName = button->getName();
	}
	return shipName;
}

string StartWindow::getSceneName(void)
{
	string sceneName = "asteroids";
	SDLComponent* component;
	if (scenesPanel->isComponentSelected())
	{
		component = scenesPanel->findSelectedComponent();
		if (component->getType() == SDLComponent::LABEL)
		{
			SDLLabel* label = static_cast<SDLLabel*>(component);
			sceneName = label->getText();
		}
	}
	return sceneName;
}

void StartWindow::init(void)
{
	delayTime = 0;
	fps = 30;
	interval = 1 * 1000 / fps;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_EnableKeyRepeat(600, SDL_DEFAULT_REPEAT_INTERVAL);
	surface = new SDLSurface(430, 550, 32);
	surface->setBackgroundColor(new Color(255, 255, 255));
	tabPanel = new SDLTabPanel(10, 10, 410, 520, surface);

	// Tab del cliente
	SDLLabel* shipLabel = new SDLLabel(20, 80, 50, 30, "Nave:", surface);

	SDLSurface* ship1Image = new SDLSurface();
	ship1Image->loadFromImage("..\\images\\nave1.png");
	SDLToggleButton* ship1 = new SDLToggleButton(20, 120, 60, 60, "", surface);
	ship1->setName("nave1");
	ship1->setImage(ship1Image);

	SDLSurface* ship2Image = new SDLSurface();
	ship2Image->loadFromImage("..\\images\\nave2.png");
	SDLToggleButton* ship2 = new SDLToggleButton(100, 120, 60, 60, "", surface);
	ship2->setName("nave2");
	ship2->setImage(ship2Image);

	SDLSurface* ship3Image = new SDLSurface();
	ship3Image->loadFromImage("..\\images\\nave3.png");
	SDLToggleButton* ship3 = new SDLToggleButton(180, 120, 60, 60, "", surface);
	ship3->setName("nave3");
	ship3->setImage(ship3Image);

	SDLSurface* ship4Image = new SDLSurface();
	ship4Image->loadFromImage("..\\images\\nave4.png");
	SDLToggleButton* ship4 = new SDLToggleButton(260, 120, 60, 60, "", surface);
	ship4->setName("nave4");
	ship4->setImage(ship4Image);

	SDLSurface* ship5Image = new SDLSurface();
	ship5Image->loadFromImage("..\\images\\nave5.png");
	SDLToggleButton* ship5 = new SDLToggleButton(340, 120, 60, 60, "", surface);
	ship5->setName("nave5");
	ship5->setImage(ship5Image);

	shipsButtonPanel = new SDLButtonPanel(surface);
	shipsButtonPanel->addButton(ship1);
	shipsButtonPanel->addButton(ship2);
	shipsButtonPanel->addButton(ship3);
	shipsButtonPanel->addButton(ship4);
	shipsButtonPanel->addButton(ship5);

	SDLLabel* hostLabel = new SDLLabel(20, 220, 50 ,30, "Host:", surface);
	hostTextbox = new SDLTextbox(100, 220, 300, 30, surface);
	hostTextbox->setText("127.0.0.1");

	SDLLabel* portLabel = new SDLLabel(20, 300, 50, 30, "Puerto:", surface);
	portTextbox = new SDLTextbox(100, 300, 300, 30, surface);
	portTextbox->setText("2555");

	SDLLabel* playerLabel = new SDLLabel(20, 380, 50, 30, "Jugador:", surface);
	playerTextbox = new SDLTextbox(100, 380, 300, 30, surface);

	SDLButton* exitButton = new SDLButton(100, 450, 80, 40, "Salir", surface);
	exitButton->setName("Cliente::Salir");
	exitButton->setMouseListener(dynamic_cast<MouseListener*>(controller));
	SDLButton* connectButton = new SDLButton(260, 450, 80, 40, "Conectar", surface);
	connectButton->setMouseListener(dynamic_cast<MouseListener*>(controller));
	connectButton->setName("Cliente::Conectar");

	SDLPanel* clientPanel = new SDLPanel(surface);
	clientPanel->addComponent(shipLabel);
	clientPanel->addComponent(shipsButtonPanel);
	clientPanel->addComponent(hostLabel);
	clientPanel->addComponent(hostTextbox);
	clientPanel->addComponent(portLabel);
	clientPanel->addComponent(portTextbox);
	clientPanel->addComponent(playerLabel);
	clientPanel->addComponent(playerTextbox);
	clientPanel->addComponent(exitButton);
	clientPanel->addComponent(connectButton);

	// Tab del servidor
	SDLLabel* portLabelServer = new SDLLabel(20, 300, 50 ,30, "Puerto:", surface);
	portTextboxServer = new SDLTextbox(100, 300, 300, 30, surface);
	portTextboxServer->setText("2555");

	SDLButton* exitButtonServer = new SDLButton(100, 450, 80, 40, "Salir", surface);
	exitButtonServer->setMouseListener(dynamic_cast<MouseListener*>(controller));
	exitButtonServer->setName("Server::Salir");
	SDLButton* startButtonServer = new SDLButton(260, 450, 80, 40, "Iniciar", surface);
	startButtonServer->setMouseListener(dynamic_cast<MouseListener*>(controller));
	startButtonServer->setName("Server::Conectar");

	scenesPanel = new SDLPanel(20, 60, 380, 220, surface);
	Layout* tableLayout = new ScrollablePanelLayout();
	scenesPanel->setLayout(tableLayout);
	/*
	SDLLabel* sceneLabel;
	list<string>::iterator it;
	for (it=sceneNames.begin(); it!=sceneNames.end(); it++)
	{
		sceneLabel = new SDLLabel(*it, surface);
		scenesPanel->addComponent(sceneLabel);
	}
	*/
	SDLScrollBar* scenesScrollBar = new SDLScrollBar(surface);
	scenesPanel->setScrollBar(scenesScrollBar);
	//scenesScrollBar->setUnitIncrement(sceneLabel->getHeight());

	SDLPanel* serverPanel = new SDLPanel(surface);
	serverPanel->addComponent(scenesPanel);
	serverPanel->addComponent(portLabelServer);
	serverPanel->addComponent(portTextboxServer);
	serverPanel->addComponent(exitButtonServer);
	serverPanel->addComponent(startButtonServer);
	
	tabPanel->addTab("Cliente", clientPanel);
	tabPanel->addTab("Servidor", serverPanel);
	statusBar = new SDLStatusBar(12, surface);
	statusBar->setStatusText("Estado: no actualizado");
	Color* statusBarBgColor = new Color(232, 232, 232);
	statusBar->setBackgroundColor(statusBarBgColor);
}

void StartWindow::handleEvents(void)
{
	SDL_Event event;
	quit = 0;
	while (!quit)
	{
		// regula FPS
		checkFramesPerSecond();
		if (SDL_PollEvent(&event))
		{
			handleEvent(event);			
		}

		// actualiza datos
		loop();

		// procesa pintado de pantalla
		render();
	}
}

void StartWindow::checkFramesPerSecond(void)
{
	if (delayTime > SDL_GetTicks())
	{
		SDL_Delay(delayTime - SDL_GetTicks());
	}
	delayTime = SDL_GetTicks() + interval;	
}

void StartWindow::loop()
{
	//double time = SDL_GetTicks();
}

void StartWindow::render()
{
	tabPanel->draw();
	statusBar->draw();
	// hace flush del buffer
	surface->paint();
}

void StartWindow::handleEvent(SDL_Event event)
{
	SDLEvent* sdlEvent = new SDLEvent(&event);
	tabPanel->processEvent(sdlEvent);
	switch (event.type)
	{
	case SDL_QUIT:
		quit = 1;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			quit = 1;
			break;
		}
		break;
	}
}

void StartWindow::setStatus (string text)
{
	statusBar->setStatusText(text);
}
