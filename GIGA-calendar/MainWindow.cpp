
#include <iostream>

#include "MainWindow.h"
#include "Settings.h"
#include "Resources.h"
#include "SlideMonth.h"



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
	unsigned int dcWidth = chWidth - Settings::Calendar::margin.left - Settings::Calendar::margin.right,
		dcHeight = chHeight - Settings::Calendar::margin.top - Settings::Calendar::margin.bottom;// -2;

	dcWidth -= (dcWidth - 6 * Settings::Calendar::spaceBetweenCells) % 7;
	dcHeight -= (dcHeight - 5 * Settings::Calendar::spaceBetweenRows) % 6;


	dateCalendar.setBackgroundTexture(Resources::Calendar::redBackground);
	dateCalendar.setBackgroundTextureRect(sf::IntRect(0, 0, dcWidth + Settings::MonthView::margin.left + Settings::MonthView::margin.right,
		dcHeight));



	Date date(Date::now().setDay(1)), end(date);

	viewPosition = date;

	date.setMonth((date.getMonth() - 1) % 12);
	date = date - date.getDayOfWeek();

	calendarTop = date;


	std::cout << "Date : {" << date.getYear() << '-' << int(date.getMonth()) << '-' << int(date.getDay()) << " [" << int(date.getDayOfWeek()) << ", w" << int(date.getWeekNumber()) << "]}" << std::endl;


	end.setMonth((end.getMonth() + 2) % 12);

	calendarBottom = end;

	end = end + 7 - end.getDayOfWeek();



	const unsigned int cellWidth = (dcWidth - 6 * Settings::Calendar::spaceBetweenCells) / 7, cellHeight = (dcHeight - 5 * Settings::Calendar::spaceBetweenRows) / 6;

	const uint8_t widthLoss = (dcWidth - 6 * Settings::Calendar::spaceBetweenCells) % 7;

	Resources::Calendar::Cell::loadBackground(cellWidth, cellHeight, Settings::Calendar::Cell::monthColors[0]);

	for (uint8_t row = 0; date != end && row < 60; row++)
		for (uint8_t cell = 0; cell < 7; cell++) {

			gui::TextArea text(std::to_string(date.getDay()), Resources::arial, Settings::Calendar::Cell::charSize);

			dateCalendar.add("year" + std::to_string(date.getYear()) + ": week" + std::to_string(date.getWeekNumber()) + ": cell" + std::to_string(cell), gui::Button()
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


	/*	const unsigned int viewWidth = dcWidth + Settings::MonthView::padding.left + Settings::MonthView::padding.right,
	viewHeight = dcHeight + Settings::MonthView::padding.top + Settings::MonthView::padding.bottom,
	viewX = Settings::MainWindow::padding.left + Settings::Calendar::margin.left - Settings::MonthView::margin.left,
	viewY = Settings::MainWindow::padding.top + Settings::Calendar::margin.top - Settings::MonthView::margin.top;
	*/

	monthView.setSize(dcWidth, dcHeight);
	monthView.setCenter(dcWidth / 2, dcHeight / 2);
	monthView.setViewport(sf::FloatRect(float(Settings::MainWindow::padding.left + Settings::Calendar::margin.left - Settings::MonthView::margin.left) / Settings::MainWindow::width,
		float(Settings::MainWindow::padding.top + Settings::Calendar::margin.top - Settings::MonthView::margin.top) / Settings::MainWindow::height,
		float(dcWidth + Settings::MonthView::margin.left + Settings::MonthView::margin.right) / width,
		float(dcHeight + Settings::MonthView::margin.top + Settings::MonthView::margin.bottom) / height));



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
			monthView.move(0, (cellHeight + Settings::Calendar::spaceBetweenRows));
		})
		.resetShader(customShader));


	Resources::Calendar::MonthScroll::Previous::loadBackground();

	calendarHUD.add("previousMonth", gui::Button().setTexture(Resources::Calendar::MonthScroll::Previous::background)
		.setPosition(nextmbX - Settings::Calendar::MonthScroll::Previous::rightMargin - Resources::Calendar::MonthScroll::Previous::background.getSize().x,
			Settings::Calendar::margin.top - Settings::Calendar::MonthScroll::Previous::bottomMargin - Resources::Calendar::MonthScroll::Previous::background.getSize().y)
		.bindAction(gui::Event::Released, [this]() {
			monthView.move(0, -10);
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


	std::cout << "viewPosition : {" << viewPosition.getYear() << '-' << int(viewPosition.getMonth()) << '-' << int(viewPosition.getDay())
		<< " [" << int(viewPosition.getDayOfWeek()) << ", w" << int(viewPosition.getWeekNumber()) << "]}" << std::endl;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::KeyReleased:
				if (event.key.code != sf::Keyboard::Escape) break;
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseWheelScrolled:
				if (windowManager.at("calendarHUD", true).contains(sf::Vector2f(event.mouseWheelScroll.x, event.mouseWheelScroll.y))) {
					monthView.move(0, event.mouseWheelScroll.delta * (-int(cellHeight) - Settings::Calendar::spaceBetweenRows));
					viewPosition = (event.mouseWheelScroll.delta < 0) ? viewPosition + (-event.mouseWheelScroll.delta * 7) : viewPosition - (event.mouseWheelScroll.delta * 7);
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

		
		window.setView(window.getDefaultView());
		window.draw(windowManager);
		


		/*std::cout << "viewPosition : {" << viewPosition.getYear() << '-' << int(viewPosition.getMonth()) << '-' << int(viewPosition.getDay())
			<< " [" << int(viewPosition.getDayOfWeek()) << ", w" << int(viewPosition.getWeekNumber()) << "]}" << std::endl;
			*/

		window.setView(monthView);
		window.draw(dateCalendar);

		window.display();
	}
}

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

		return toReturn;
}
