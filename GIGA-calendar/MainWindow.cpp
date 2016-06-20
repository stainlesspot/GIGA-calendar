
#include <iostream>

#include "MainWindow.h"
#include "Settings.h"
#include "Resources.h"

std::unique_ptr<Date> MainWindow::Calendar::Cell::highlighted(nullptr);

const gui::Button& MainWindow::Calendar::Cell::generateButton()
{
	Date date(date);
	gui::TextArea text(std::to_string(date.getDay()), Resources::arial, Settings::Calendar::Cell::charSize);

	button.setTexture(Resources::Calendar::Cell::background)
		.setPosition(position)
		.setName(text.setColor(Settings::Calendar::Cell::textColor).setPosition((text.getGlobalBounds().width - width) / 2 + 8, (text.getGlobalBounds().height - height / 2)))
		.setColor(Settings::Calendar::Cell::monthColors[date.getMonth()])
		.bindAction(gui::Event::Released, [date]() {
			MainWindow::Calendar::Cell::highlighted.reset(new Date(date));
		})
		.resetShader(
			"uniform float state;\
			uniform bool active;\
			uniform sampler2D tex;\
			\
			void main()\
			{\
				vec4 color = texture2D(tex, gl_TexCoord[0].xy) * gl_Color;\
				if (active)\
					gl_FragColor = vec4((color.rgb == vec3(1, 1, 1)) ? color.rgb : (color.rgb * (1.0f - (state * " + std::to_string(Settings::Calendar::Cell::shaderDarkening) + "f))), color.a);\
				else\
				{\
					float greyValue = color.r * 0.29 + color.g * 0.58 + color.b * 0.13;\
					gl_FragColor = vec4(greyValue, greyValue, greyValue, color.a);\
				}\
			}");

	return button;
}

const gui::Button & MainWindow::Calendar::Cell::updateButton()
{
	Date date(date);
	gui::TextArea text(std::to_string(date.getDay()), Resources::arial, Settings::Calendar::Cell::charSize);

	button.setPosition(position)
		.setName(text.setColor(Settings::Calendar::Cell::textColor).setPosition((text.getGlobalBounds().width - width) / 2 + 8, (text.getGlobalBounds().height - height / 2)))
		.setColor(Settings::Calendar::Cell::monthColors[date.getMonth()])
		.bindAction(gui::Event::Released, [date]() {
			MainWindow::Calendar::Cell::highlighted.reset(new Date(date));
		});

	return button;
}

void MainWindow::Calendar::Cell::operator--()
{
	--date;
	position.x -= width + Settings::Calendar::spaceBetweenCells;
	if (position.x < 0)
		position = sf::Vector2f((width + Settings::Calendar::spaceBetweenCells) * 6, position.y - height - Settings::Calendar::spaceBetweenRows);
}

void MainWindow::Calendar::Cell::operator++()
{
	++date;
	position.x += width + Settings::Calendar::spaceBetweenCells;

	if (position.x >(width + Settings::Calendar::spaceBetweenCells) * 6)
		position = sf::Vector2f(0, position.y + height + Settings::Calendar::spaceBetweenRows);
}


void MainWindow::Calendar::move(const int16_t rows)
{
	viewPosition = viewPosition + rows * 7;
	viewOffset += rows;

	view.move(0, rows * (first.height + Settings::Calendar::spaceBetweenRows));

	load(rows <= 0, rows * (rows < 0 ? -1 : 1));
	unload(rows > 0, rows * (rows < 0 ? -1 : 1));
}

void MainWindow::Calendar::load(const bool beforeFirst, const uint16_t numberOfRows, const bool calibrate)
{
	if (beforeFirst) {
		Date end(first.date - numberOfRows * 7);

		while (first.date != end) {
			--first;
			window.add(first.date.asString(), first.updateButton());
		}
	}
	else {
		Date end(last.date + numberOfRows * 7 - calibrate);

		while (last.date != end) {
			++last;
			window.add(last.date.asString(), last.updateButton());
		}
	}
}

void MainWindow::Calendar::unload(const bool afterFirst, const uint16_t numberOfRows)
{
	if (afterFirst) {
		Date date(first.date), end(date + numberOfRows * 7);

		while (date != end) {
			window.erase(date.asString());
			++date;
		}

		first.date = date;
		first.position.y += numberOfRows * (first.height + Settings::Calendar::spaceBetweenRows);
	}
	else {
		Date date(last.date), end(date - numberOfRows * 7);

		while (date != end) {
			window.erase(date.asString());
			--date;
		}

		last.date = date;
		last.position.y -= numberOfRows * (last.height + Settings::Calendar::spaceBetweenRows);
	}
}

void MainWindow::initialize()
{
	//	Calendar:

	const unsigned int chWidth = Settings::MainWindow::width * 2 / 3 + (Settings::MainWindow::width % 3 == 2) - Settings::MainWindow::padding.left,
		chHeight = Settings::MainWindow::height - Settings::MainWindow::padding.top - Settings::MainWindow::padding.bottom;

	calendar.width = chWidth - Settings::Calendar::margin.left - Settings::Calendar::margin.right;
	calendar.height = chHeight - Settings::Calendar::margin.top - Settings::Calendar::margin.bottom;
	

	Date date(Date::now().setDay(1)), end(date);

	calendar.viewPosition = date.getMonday();

	date.setMonth(date.getMonth() - Settings::Calendar::preemtiveMonthLoad);
		
	end.setMonth(end.getMonth() + Settings::Calendar::preemtiveMonthLoad + 1);
	--end;


	calendar.start = date = date.getMonday();

	calendar.first.date = calendar.last.date = date;
	
	const unsigned int cellWidth = (calendar.width - 6 * Settings::Calendar::spaceBetweenCells) / 7,
		cellHeight = (calendar.height - (Settings::Calendar::numberOfRows - 1) * Settings::Calendar::spaceBetweenRows) / Settings::Calendar::numberOfRows;

	Resources::load(Resources::Calendar::Cell::background, cellWidth, cellHeight, Settings::Calendar::Cell::monthColors[0]);

	calendar.first.position = calendar.last.position = sf::Vector2f(0, 0);

	calendar.first.width = calendar.last.width = cellWidth;
	calendar.first.height = calendar.last.height = cellHeight;

	calendar.window.add(calendar.last.date.asString(), calendar.last.generateButton());

	calendar.first.generateButton();


	calendar.load(false, end.getWeekNumber() - date.getWeekNumber(), true);


	// Calendar View

	calendar.viewOffset = (calendar.viewPosition - calendar.start).asDays() / 7;

	calendar.view.setSize(calendar.width, calendar.height);
	calendar.view.setCenter(calendar.width / 2, calendar.height / 2 +  calendar.viewOffset * (cellHeight + Settings::Calendar::spaceBetweenRows));


	const sf::IntRect viewRect(Settings::MainWindow::padding.left + Settings::Calendar::margin.left - Settings::MonthView::margin.left,
		Settings::MainWindow::padding.top + Settings::Calendar::margin.top - Settings::MonthView::margin.top,
		calendar.width + Settings::MonthView::margin.left + Settings::MonthView::margin.right,
		calendar.height + Settings::MonthView::margin.top + Settings::MonthView::margin.bottom);

	calendar.view.setViewport(sf::FloatRect(float(viewRect.left) / Settings::MainWindow::width,
		float(viewRect.top) / Settings::MainWindow::height,
		float(viewRect.width) / Settings::MainWindow::width,
		float(viewRect.height) / Settings::MainWindow::height));



	// Calendar Hud:

	calendar.hud.setPosition(Settings::MainWindow::padding.left, Settings::MainWindow::padding.top);


	Resources::load(Resources::Calendar::background, chWidth, chHeight, Settings::Calendar::backgroundColor);

	calendar.hud.setBackgroundTexture(Resources::Calendar::background);

	Resources::load(Resources::Calendar::MonthScroll::Next::background, "resources/arrow_down.png");

	const unsigned int nextmbX = chWidth - Settings::Calendar::MonthScroll::Next::rightMargin - Resources::Calendar::MonthScroll::Next::background.getSize().x - Settings::Calendar::margin.right;


	std::string customShader(
		"uniform float state;\
			uniform bool active;\
			uniform sampler2D tex;\
			\
			void main()\
			{\
				vec4 color = texture2D(tex, gl_TexCoord[0].xy) * gl_Color;\
				if (active)\
					gl_FragColor = vec4((color.rgb == vec3(1, 1, 1)) ? color.rgb : (color.rgb * (1.0f - (state * 0.40f))), color.a);\
				else\
				{\
					float greyValue = color.r * 0.29 + color.g * 0.58 + color.b * 0.13;\
					gl_FragColor = vec4(greyValue, greyValue, greyValue, color.a);\
				}\
			}");

	calendar.hud.add("nextMonth", gui::Button().setTexture(Resources::Calendar::MonthScroll::Next::background)
		.setPosition(nextmbX, Settings::Calendar::margin.top - Settings::Calendar::MonthScroll::Next::bottomMargin - Resources::Calendar::MonthScroll::Next::background.getSize().y)
		.bindAction(gui::Event::Released, [this]() {
			Date newViewPosition(calendar.viewPosition + (Settings::Calendar::numberOfRows + 1) / 2 * 7);
			newViewPosition.addMonths(1).setDay(1);

			calendar.move((newViewPosition - calendar.viewPosition).asDays() / 7);
		})
		.resetShader(customShader));


	Resources::load(Resources::Calendar::MonthScroll::Previous::background, "resources/arrow_up.png");

	calendar.hud.add("previousMonth", gui::Button().setTexture(Resources::Calendar::MonthScroll::Previous::background)
		.setPosition(nextmbX - Settings::Calendar::MonthScroll::Previous::rightMargin - Resources::Calendar::MonthScroll::Previous::background.getSize().x,
			Settings::Calendar::margin.top - Settings::Calendar::MonthScroll::Previous::bottomMargin - Resources::Calendar::MonthScroll::Previous::background.getSize().y)
		.bindAction(gui::Event::Released, [this]() {
			Date newViewPosition(calendar.viewPosition + (Settings::Calendar::numberOfRows + 1) / 2 * 7);
			newViewPosition.addMonths(-1).setDay(1);
			newViewPosition = newViewPosition.getMonday();

			calendar.move((long long(newViewPosition.asDays()) - long long(calendar.viewPosition.asDays())) / 7);
		})
		.resetShader(customShader));





	//	ActivityMenu:

/*	const unsigned int //amWidth(Settings::MainWindow::width / 3 + ((Settings::MainWindow::width % 3 == 2) ? 1 : 0) - Settings::MainWindow::padding.right),
		amHeight(Settings::MainWindow::height - Settings::MainWindow::padding.top - Settings::MainWindow::padding.bottom),
		ewWidth(amWidth - Settings::ActivityMenu::EventNode::margin.left - Settings::ActivityMenu::EventNode::margin.right),
		ewHeight(amHeight - Settings::ActivityMenu::EventNode::margin.top - Settings::ActivityMenu::EventNode::margin.bottom);
*/

	const sf::IntRect

		activityMenuRect(Settings::MainWindow::width * 2 / 3,
			Settings::MainWindow::padding.top,
			Settings::MainWindow::width / 3 + ((Settings::MainWindow::width % 3 == 2) ? 1 : 0) - Settings::MainWindow::padding.right,
			Settings::MainWindow::height - Settings::MainWindow::padding.top - Settings::MainWindow::padding.bottom),

		eventNodeRect(activityMenuRect.left + Settings::ActivityMenu::EventNode::margin.left,
			activityMenuRect.height + Settings::ActivityMenu::EventNode::margin.top,
			activityMenuRect.width - Settings::ActivityMenu::EventNode::margin.left - Settings::ActivityMenu::EventNode::margin.right,
			(activityMenuRect.height - Settings::ActivityMenu::EventNode::margin.top - Settings::ActivityMenu::EventNode::margin.bottom
				- (Settings::ActivityMenu::EventNode::numberOfRows - 1) * Settings::ActivityMenu::EventNode::spaceBetweenRows) / Settings::ActivityMenu::EventNode::numberOfRows);


	Resources::load(Resources::ActivityMenu::background, activityMenuRect.width, activityMenuRect.height, Settings::ActivityMenu::backgroundColor);


	gui::TextArea highlightedDateMsg("No date selected", Resources::arial, 35);

	sf::FloatRect msgBounds(highlightedDateMsg.getGlobalBounds());



	Resources::load(Resources::ActivityMenu::EventNode::background, eventNodeRect.width, eventNodeRect.height, Settings::ActivityMenu::EventNode::backgroundColor);

/*	eventWindow.setActive(false)
		.setPosition(Settings::MainWindow::width * 2 / 3 + Settings::ActivityMenu::EventNode::margin.left, Settings::MainWindow::padding.top + Settings::ActivityMenu::EventNode::margin.top)
		.setBackgroundTexture(Resources::ActivityMenu::EventNode::background);
*/


	std::unique_ptr<Date> previousHighlight(nullptr);



	activityMenu.setPosition(Settings::MainWindow::width * 2 / 3, Settings::MainWindow::padding.top)
		.setBackgroundTexture(Resources::ActivityMenu::background)
		.add("highlightedDate", highlightedDateMsg.setPosition((activityMenuRect.width - msgBounds.width - msgBounds.left) / 2, (activityMenuRect.height - msgBounds.height - msgBounds.top) / 2)
			.setUpdateFunction([this, activityMenuRect, eventNodeRect, &previousHighlight]() {	
				if (Calendar::Cell::highlighted != nullptr) {
					sf::FloatRect newMsgBounds(sf::Text(Calendar::Cell::highlighted->asString("D M Y"), Resources::arial, 35).getGlobalBounds());
					
					if (previousHighlight == nullptr)
						windowManager.at("activityMenu", true).at("highlightedDate").setPosition(activityMenuRect.left + (activityMenuRect.width - newMsgBounds.width - newMsgBounds.left) / 2,
							activityMenuRect.top - newMsgBounds.top + Settings::ActivityMenu::HighlightedDateMsg::marginTop);
					else if (*previousHighlight != *Calendar::Cell::highlighted) {
						
				//		windowManager.at("eventWindow", true).setActive(true);

						for (uint8_t row = 0; row < Settings::ActivityMenu::EventNode::numberOfRows; row++) {
							this->windowManager.at("activityMenu", true)
								.add("row" + std::to_string(row) + " text",
									gui::TextField(Resources::arial, eventNodeRect.width, Settings::ActivityMenu::EventNode::characterSize)
									.setPosition(eventNodeRect.left, eventNodeRect.top + (eventNodeRect.height + Settings::ActivityMenu::EventNode::spaceBetweenRows) * row)
									.setColor(sf::Color::Black)
									.setPrompt(gui::bind("Click to add new Event", sf::Color(140, 140, 140, 255))))
								.add("row" + std::to_string(row) + "background",
									gui::Icon(Resources::ActivityMenu::EventNode::background)
									.setPosition(eventNodeRect.left, eventNodeRect.top + (eventNodeRect.height + Settings::ActivityMenu::EventNode::spaceBetweenRows) * row));
							std::cout << "__KON" << int(row) << std::endl;
						}
						std::cout << "ended KON";
					}

					previousHighlight.reset(new Date(*Calendar::Cell::highlighted));
					return gui::bind(Calendar::Cell::highlighted->asString("D M Y"), sf::Color::White);
				}
				previousHighlight.reset(nullptr);
				return gui::bind("No date selected", sf::Color::White);
			}));



	windowManager.emplace("calendarHud", calendar.hud, true);

//	windowManager.emplace("eventWindow", eventWindow, true);
	windowManager.emplace("activityMenu", activityMenu, true);





	sf::RenderWindow window(sf::VideoMode(Settings::MainWindow::width, Settings::MainWindow::height), "GIGA-Calendar", sf::Style::None);
	
	window.setVerticalSyncEnabled(true);


	sf::View test;
	test = window.getDefaultView();
	test.setSize(3000, 3000);

	bool testMode = false;

	
	
	
	
	
	sf::Text _text("9", Resources::arial, 9);
	_text.setColor(sf::Color::Black);

	gui::TextArea _text2("35", Resources::arial, 35);
	_text2.setPosition(Settings::MainWindow::width / 2, -8);


	sf::Clock _timer;



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::KeyReleased:
				if (event.key.control)
					switch (event.key.code) {
					case sf::Keyboard::T:
						testMode = testMode ? false : true;
						break;
					case sf::Keyboard::F:
						if (windowManager.at("activityMenu", true).exists("fpsMeter"))
							windowManager.at("activityMenu", true).erase("fpsMeter");
						else
							windowManager.at("activityMenu", true).add("fpsMeter", gui::FPSMeter(Resources::arial, Settings::Calendar::Cell::charSize).setColor(sf::Color::White).setPosition(10, 0));

						break;
					case sf::Keyboard::V:
						if (windowManager.at("activityMenu", true).exists("viewPosition"))
							windowManager.at("activityMenu", true).erase("viewPosition");
						else
							windowManager.at("activityMenu", true).add("viewPosition", gui::TextArea(calendar.viewPosition.asString(), Resources::arial, Settings::Calendar::Cell::charSize)
								.setColor(sf::Color::White).setPosition(10, 200)
								.setUpdateFunction([this]() {
									return gui::bind(calendar.viewPosition.asString(), sf::Color::White);
								}));

						break;
					case sf::Keyboard::P:
						_text2.setCharacterSize(_text2.getCharacterSize() + 1);
						_text2.setText(std::to_string(_text2.getCharacterSize()));
						break;
					}
				
				if (event.key.code != sf::Keyboard::Escape) break;

			case sf::Event::Closed:
				window.close();
				break;
			
			case sf::Event::MouseWheelScrolled:
				if (windowManager.at("calendarHud", true).contains(sf::Vector2f(event.mouseWheelScroll.x, event.mouseWheelScroll.y)))
					calendar.move(-int(event.mouseWheelScroll.delta));
				break;

			default:
				bool contains = false;
				if (event.type == sf::Event::MouseMoved && viewRect.contains(event.mouseMove.x, event.mouseMove.y)) {
					event.mouseMove.x -= viewRect.left;
					event.mouseMove.y -= viewRect.top - calendar.viewOffset * (cellHeight + Settings::Calendar::spaceBetweenRows);
					contains = true;
				}
				else if ((event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) && viewRect.contains(event.mouseButton.x, event.mouseButton.y)) {
					event.mouseButton.x -= viewRect.left;
					event.mouseButton.y -= viewRect.top - calendar.viewOffset * (cellHeight + Settings::Calendar::spaceBetweenRows);
					contains = true;
				}
				if(contains == true)
					if(calendar.window.input(event)) break;
		
				windowManager.input(event);

				break;
			}
		}

		window.clear(Settings::MainWindow::backgroundColor);


		if (!testMode) {
			window.setView(window.getDefaultView());
			window.draw(windowManager);

			window.setView(calendar.view);
		}
		else
			window.setView(test);
		window.draw(calendar.window);
		
		
		
	/*
		if (_timer.getElapsedTime() >= sf::seconds(1)) {
			_text.setCharacterSize(_text.getCharacterSize() + 1);

			_text.setString(std::to_string(_text.getCharacterSize()));

			_timer.restart();
		}
		
		*/
		
	//	window.draw(_text);
	//	window.draw(_text2);
		
		
		
		
		
		
		window.display();
	}
}

