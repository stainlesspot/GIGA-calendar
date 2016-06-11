
#include <iostream>

#include "MainWindow.h"
#include "Settings.h"
#include "Resources.h"
#include "SlideMonth.h"



<<<<<<< HEAD
=======
 struct MainWindow::Calendar{

	 struct Cell {
		 uint16_t width, height;

		 sf::Vector2f position;

		 Date date;

		 const std::unique_ptr<gui::Button> asButton() const;
	 };

	 uint16_t width, height, cellWidth, cellHeight;

	 sf::View view;

	 gui::Window window;

	 uint8_t viewPosition;
	 Cell first, last;

	 void load(const bool aboveFirst, const uint16_t numberOfRows);
	 void unload(const bool atFirst, const uint16_t numberOfRows);

 };

>>>>>>> origin/master
 



MainWindow::MainWindow()
	: width(Settings::MainWindow::width), height(Settings::MainWindow::height)
	/*,dateCalendar(sf::Vector2f(Settings::MainWindow::padding.left, Settings::MainWindow::padding.top), width * 2 / 3 + ((width % 3 == 2) ? 1 : 0) - Settings::MainWindow::padding.left,
		height - Settings::MainWindow::padding.top - Settings::MainWindow::padding.bottom)*/
{
	
}


void MainWindow::initialize()
{
	//	DateCalendar:


	const unsigned int chWidth = width * 2 / 3 + (width % 3 == 2) - Settings::MainWindow::padding.left,
		chHeight = height - Settings::MainWindow::padding.top - Settings::MainWindow::padding.bottom;

	calendar.width = chWidth - Settings::Calendar::margin.left - Settings::Calendar::margin.right;
	calendar.height = chHeight - Settings::Calendar::margin.top - Settings::Calendar::margin.bottom;

//	dcWidth -= (dcWidth - 6 * Settings::Calendar::spaceBetweenCells) % 7;
//	dcHeight -= (dcHeight - 5 * Settings::Calendar::spaceBetweenRows) % 6;


	calendar.window.setBackgroundTexture(Resources::Calendar::redBackground);
	calendar.window.setBackgroundTextureRect(sf::IntRect(0, 0, calendar.width + Settings::MonthView::margin.left + Settings::MonthView::margin.right, calendar.height));



	Date date(Date::now().setDay(1)), end(date);

	calendar.viewPosition = date.getWeekNumber();

	date.setMonth(date.getMonth() - Settings::Calendar::preemtiveMonthLoad);
	
//	calendar.viewPosition = date.getWeekNumber() - calendar.viewPosition;
	
	end.setMonth(end.getMonth() + Settings::Calendar::preemtiveMonthLoad + 1);
	--end;

	//std::cout << "date days : " << date.asDays() << "\ndayofweek : " << int(date.getDayOfWeek());

	date = date.asDays() - date.getDayOfWeek();

	calendar.first.date = calendar.last.date = date;
	
//	std::cout << "Date : {" << date.getYear() << '-' << int(date.getMonth()) << '-' << int(date.getDay()) << " [" << int(date.getDayOfWeek()) << ", w" << int(date.getWeekNumber()) << "]}" << std::endl;

	const unsigned int cellWidth = (calendar.width - 6 * Settings::Calendar::spaceBetweenCells) / 7,
		cellHeight = (calendar.height - 5 * Settings::Calendar::spaceBetweenRows) / 6;

	Resources::Calendar::Cell::loadBackground(cellWidth, cellHeight, Settings::Calendar::Cell::monthColors[0]);

	calendar.first.position = calendar.last.position = sf::Vector2f(0, 0);

	calendar.first.width = calendar.last.width = cellWidth;
	calendar.first.height = calendar.last.height = cellHeight;

<<<<<<< HEAD
	calendar.window.add(calendar.last.date.asString(), calendar.last.generateButton());

	calendar.first.generateButton();
=======
			
			date = date + 1;
		}
>>>>>>> origin/master

	calendar.load(false, end.getWeekNumber() - date.getWeekNumber(), true);

	/*	const unsigned int viewWidth = dcWidth + Settings::MonthView::padding.left + Settings::MonthView::padding.right,
	viewHeight = dcHeight + Settings::MonthView::padding.top + Settings::MonthView::padding.bottom,
	viewX = Settings::MainWindow::padding.left + Settings::Calendar::margin.left - Settings::MonthView::margin.left,
	viewY = Settings::MainWindow::padding.top + Settings::Calendar::margin.top - Settings::MonthView::margin.top;
	*/

	calendar.view.setSize(calendar.width, calendar.height);
	calendar.view.setCenter(calendar.width / 2, calendar.height / 2 + (calendar.viewPosition - date.getWeekNumber())  * (cellHeight + Settings::Calendar::spaceBetweenRows));
	calendar.view.setViewport(sf::FloatRect(float(Settings::MainWindow::padding.left + Settings::Calendar::margin.left - Settings::MonthView::margin.left) / Settings::MainWindow::width,
		float(Settings::MainWindow::padding.top + Settings::Calendar::margin.top - Settings::MonthView::margin.top) / Settings::MainWindow::height,
		float(calendar.width + Settings::MonthView::margin.left + Settings::MonthView::margin.right) / width,
		float(calendar.height + Settings::MonthView::margin.top + Settings::MonthView::margin.bottom) / height));



	// CalendarHUD:

	calendarHUD.setPosition(Settings::MainWindow::padding.left, Settings::MainWindow::padding.top);


	Resources::Calendar::loadBackground(chWidth, chHeight, Settings::Calendar::backgroundColor);

	calendarHUD.setBackgroundTexture(Resources::Calendar::background);


	Resources::Calendar::MonthScroll::Next::loadBackground();

	const unsigned int nextmbX = chWidth - Settings::Calendar::MonthScroll::Next::rightMargin - Resources::Calendar::MonthScroll::Next::background.getSize().x - Settings::Calendar::margin.right;


	std::string customShader("uniform float state;\
						uniform bool active;\
						uniform sampler2D tex;\
						\
						void main()\
						{\
							vec4 color = texture2D(tex, gl_TexCoord[0].xy) * gl_Color;\
							if (active){\
								if(state == 1 || color.a != 0)\
									gl_FragColor = color;\
								else  if (color.a == 0)\
									gl_FragColor = vec4(62.0f / 255, 230.0f / 255, 123.0f / 255, 1);\
							}\
							else\
							{\
								float greyValue = color.r * 0.29 + color.g * 0.58 + color.b * 0.13;\
								gl_FragColor = vec4(greyValue, greyValue, greyValue, color.a);\
							}\
						}");

	calendarHUD.add("nextMonth", gui::Button().setTexture(Resources::Calendar::MonthScroll::Next::background)
		.setPosition(nextmbX, Settings::Calendar::margin.top - Settings::Calendar::MonthScroll::Next::bottomMargin - Resources::Calendar::MonthScroll::Next::background.getSize().y)
		.bindAction(gui::Event::Released, [this, cellHeight]() {
			calendar.view.move(0, (cellHeight + Settings::Calendar::spaceBetweenRows));
		})
		.resetShader(customShader));


	Resources::Calendar::MonthScroll::Previous::loadBackground();

	calendarHUD.add("previousMonth", gui::Button().setTexture(Resources::Calendar::MonthScroll::Previous::background)
		.setPosition(nextmbX - Settings::Calendar::MonthScroll::Previous::rightMargin - Resources::Calendar::MonthScroll::Previous::background.getSize().x,
			Settings::Calendar::margin.top - Settings::Calendar::MonthScroll::Previous::bottomMargin - Resources::Calendar::MonthScroll::Previous::background.getSize().y)
		.bindAction(gui::Event::Released, [this]() {
			calendar.view.move(0, -10);
		})
		.resetShader(customShader));




	//	ActivityMenu:

	const unsigned int amWidth(width / 3 + ((width % 3 == 2) ? 1 : 0) - Settings::MainWindow::padding.right),
		amHeight(height - Settings::MainWindow::padding.top - Settings::MainWindow::padding.bottom);

	Resources::ActivityMenu::loadBackground(amWidth, amHeight, Settings::ActivityMenu::backgroundColor);

	gui::TextArea noDateMsg("No date selected", Resources::arial, 35);

	activityMenu.setPosition(width * 2 / 3, Settings::MainWindow::padding.top)
		.setBackgroundTexture(Resources::ActivityMenu::background)
		.add("noDateSelectedMessage", noDateMsg.setPosition((amWidth - noDateMsg.getGlobalBounds().width) / 2, (amHeight - noDateMsg.getGlobalBounds().height) / 2));





	windowManager.emplace("calendarHUD", calendarHUD, true);
	windowManager.emplace("activityMenu", activityMenu, true);





	sf::RenderWindow window(sf::VideoMode(width, height), "GIGA-Calendar", sf::Style::None);
	
	window.setVerticalSyncEnabled(true);

	/*
	SlideMonth slideDown(false, windowManager.at("dateCalendar", true));
	slideDown.setDuration(4).setFPS(20);
	*/


/*	std::cout << "viewPosition : {" << viewPosition.getYear() << '-' << int(viewPosition.getMonth()) << '-' << int(viewPosition.getDay())
		<< " [" << int(viewPosition.getDayOfWeek()) << ", w" << int(viewPosition.getWeekNumber()) << "]}" << std::endl;
*/



	sf::View test;
	test = window.getDefaultView();
	test.setSize(3000, 3000);

	bool testMode = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::T)
					testMode = testMode ? false : true;
				if (event.key.code != sf::Keyboard::Escape) break;
				
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseWheelScrolled:
				if (windowManager.at("calendarHUD", true).contains(sf::Vector2f(event.mouseWheelScroll.x, event.mouseWheelScroll.y))) {
					
					const int delta = event.mouseWheelScroll.delta;

					calendar.view.move(0, delta * (-int(cellHeight) - Settings::Calendar::spaceBetweenRows));

					if (delta < 0) {
						calendar.load(false, -delta);
						calendar.unload(true, -delta);
					}
					else {
						calendar.load(true, delta);
						calendar.unload(false, delta);
					}

				//	viewPosition = (event.mouseWheelScroll.delta < 0) ? viewPosition + (-event.mouseWheelScroll.delta * 7) : viewPosition - (event.mouseWheelScroll.delta * 7);
			/*		std::cout << "delta : " << event.mouseWheelScroll.delta << "\n";
					std::cout << "viewPosition : {" << viewPosition.getYear() << '-' << int(viewPosition.getMonth()) << '-' << int(viewPosition.getDay())
						<< " [" << int(viewPosition.getDayOfWeek()) << ", w" << int(viewPosition.getWeekNumber()) << "]}" << std::endl;
			*/	}
				break;
			default:
				windowManager.input(event);
				break;
			}
		}

		window.clear(Settings::MainWindow::backgroundColor);

	
		/*std::cout << "viewPosition : {" << viewPosition.getYear() << '-' << int(viewPosition.getMonth()) << '-' << int(viewPosition.getDay())
		<< " [" << int(viewPosition.getDayOfWeek()) << ", w" << int(viewPosition.getWeekNumber()) << "]}" << std::endl;
		*/



		if (!testMode) {
			window.setView(window.getDefaultView());
			window.draw(windowManager);

			window.setView(calendar.view);
		}
		else
			window.setView(test);
		window.draw(calendar.window);

		window.display();
	}
}

<<<<<<< HEAD
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


const gui::Button& MainWindow::Calendar::Cell::generateButton()
{

	gui::TextArea text(std::to_string(date.getDay()), Resources::arial, Settings::Calendar::Cell::charSize);

	button.setTexture(Resources::Calendar::Cell::background)
=======
void MainWindow::Calendar::load(const bool aboveTop, const uint16_t numberOfRows)
{
	if (aboveTop) {
		cellWidth = (width - 6 * Settings::Calendar::spaceBetweenCells) / 7;
		cellHeight = (height - 5 * Settings::Calendar::spaceBetweenRows) / 6;

	//	const uint8_t widthLoss = (width - 6 * Settings::Calendar::spaceBetweenCells) % 7;

		Resources::Calendar::Cell::loadBackground(cellWidth, cellHeight, Settings::Calendar::Cell::monthColors[0]);

		Date end(top - numberOfRows * 7);

		while (top != end)
			for (uint8_t cell = 0; cell < 7; cell++, top--) {

				gui::TextArea text(std::to_string(top.getDay()), Resources::arial, Settings::Calendar::Cell::charSize);

				window.add(top.asString(), gui::Button()
					.setTexture(Resources::Calendar::Cell::background)
					.setPosition((cellWidth + Settings::Calendar::spaceBetweenCells) * cell + ((cell >= 5) ? widthLoss : 0),
					(cellHeight + Settings::Calendar::spaceBetweenRows) * (row /*+ start.getWeekNumber() - viewPosition.getWeekNumber()*/))
					.setName(text.setColor(Settings::Calendar::Cell::textColor).setPosition((text.getGlobalBounds().width - cellWidth) / 2 + 8, (text.getGlobalBounds().height - cellHeight / 2)))
					.setColor(Settings::Calendar::Cell::monthColors[date.getMonth()])
					.bindAction(gui::Event::Released, [date]() {
					Resources::Calendar::Cell::highlighted.reset(new Date(date));
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
						}")
					);



				date = date + 1;
			}
	}
}

const std::unique_ptr<gui::Button> MainWindow::Calendar::Cell::asButton() const
{

	std::unique_ptr<gui::Button> toReturn(new gui::Button);

	gui::TextArea text(std::to_string(date.getDay()), Resources::arial, Settings::Calendar::Cell::charSize);

	toReturn->setTexture(Resources::Calendar::Cell::background)
>>>>>>> origin/master
		.setPosition(position)
		.setName(text.setColor(Settings::Calendar::Cell::textColor).setPosition((text.getGlobalBounds().width - width) / 2 + 8, (text.getGlobalBounds().height - height / 2)))
		.setColor(Settings::Calendar::Cell::monthColors[date.getMonth()])
		.bindAction(gui::Event::Released, [this]() {
			Resources::Calendar::Cell::highlighted.reset(new Date(date));
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

<<<<<<< HEAD
		return button;
}

const gui::Button & MainWindow::Calendar::Cell::updateButton()
{
	gui::TextArea text(std::to_string(date.getDay()), Resources::arial, Settings::Calendar::Cell::charSize);

	button.setPosition(position)
		.setName(text.setColor(Settings::Calendar::Cell::textColor).setPosition((text.getGlobalBounds().width - width) / 2 + 8, (text.getGlobalBounds().height - height / 2)))
		.setColor(Settings::Calendar::Cell::monthColors[date.getMonth()]);

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

	if (position.x > (width + Settings::Calendar::spaceBetweenCells) * 6)
		position = sf::Vector2f(0, position.y + height + Settings::Calendar::spaceBetweenRows);
=======
		return toReturn;
>>>>>>> origin/master
}
