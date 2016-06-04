
#include <iostream>

#include "MainWindow.h"
#include "Settings.h"
#include "Resources.h"
#include "SlideMonth.h"

MainWindow::MainWindow()
	: width(Settings::MainWindow::width), height(Settings::MainWindow::height)
	/*,dateCalendar(sf::Vector2f(Settings::MainWindow::padding.left, Settings::MainWindow::padding.top), width * 2 / 3 + ((width % 3 == 2) ? 1 : 0) - Settings::MainWindow::padding.left,
		height - Settings::MainWindow::padding.top - Settings::MainWindow::padding.bottom)*/
{
// CalendarHUD:

	calendarHUD.setPosition(Settings::MainWindow::padding.left, Settings::MainWindow::padding.top);

	const unsigned int chWidth = width * 2 / 3 + ((width % 3 == 2) ? 1 : 0) - Settings::MainWindow::padding.left,
		chHeight = height - Settings::MainWindow::padding.top - Settings::MainWindow::padding.bottom;

	Resources::Calendar::loadBackground(chWidth, chHeight, Settings::Calendar::backgroundColor);

	calendarHUD.setBackgroundTexture(Resources::Calendar::background);

	
	Resources::Calendar::MonthScroll::Next::loadBackground();

	const unsigned int nextmbX = chWidth - Settings::Calendar::MonthScroll::Next::rightMargin - Resources::Calendar::MonthScroll::Next::background.getSize().x - Settings::Calendar::margin.right;



	calendarHUD.add("nextMonth", gui::Button().setTexture(Resources::Calendar::MonthScroll::Next::background)
		.setPosition(nextmbX, Settings::Calendar::margin.top - Settings::Calendar::MonthScroll::Next::bottomMargin - Resources::Calendar::MonthScroll::Next::background.getSize().y)
		.resetShader("uniform float state;\
						uniform bool active;\
						uniform sampler2D tex;\
						\
						void main()\
						{\
							vec4 color = texture2D(tex, gl_TexCoord[0].xy) * gl_Color;\
							if (active){\
								if(state == 1)\
									gl_FragColor = color;\
								else  if (color.a == 0)\
									gl_FragColor = vec4(0, 1, 0, 1);\
							}\
							else\
							{\
								float greyValue = color.r * 0.29 + color.g * 0.58 + color.b * 0.13;\
								gl_FragColor = vec4(greyValue, greyValue, greyValue, color.a);\
							}\
						}"));


	Resources::Calendar::MonthScroll::Previous::loadBackground();

	calendarHUD.add("previousMonth", gui::Button().setTexture(Resources::Calendar::MonthScroll::Previous::background)
		.setPosition(nextmbX - Settings::Calendar::MonthScroll::Previous::rightMargin - Resources::Calendar::MonthScroll::Previous::background.getSize().x,
			Settings::Calendar::margin.top - Settings::Calendar::MonthScroll::Previous::bottomMargin - Resources::Calendar::MonthScroll::Previous::background.getSize().y)
		.resetShader("uniform float state;\
						uniform bool active;\
						uniform sampler2D tex;\
						\
						void main()\
						{\
							vec4 color = texture2D(tex, gl_TexCoord[0].xy) * gl_Color;\
							if (active){\
								if(state == 1)\
									gl_FragColor = color;\
								else  if (color.a == 0)\
									gl_FragColor = vec4(0, 1, 0, 1);\
							}\
							else\
							{\
								float greyValue = color.r * 0.29 + color.g * 0.58 + color.b * 0.13;\
								gl_FragColor = vec4(greyValue, greyValue, greyValue, color.a);\
							}\
						}"));




//	DateCalendar:

	const unsigned int dcWidth = chWidth - Settings::Calendar::margin.left - Settings::Calendar::margin.right,
		dcHeight = chHeight - Settings::Calendar::margin.top - Settings::Calendar::margin.bottom;
	

	dateCalendar.setBackgroundTexture(Resources::Calendar::redBackground);
	dateCalendar.setBackgroundTextureRect(sf::IntRect(0, 0, dcWidth + Settings::MonthView::padding.left + Settings::MonthView::padding.right,
		dcHeight + Settings::MonthView::padding.top + Settings::MonthView::padding.bottom));

	
	
	Date date(Date::now().setDay(1));

	date = date - date.getDayOfWeek();

	const unsigned int cellWidth = (dcWidth - 6 * Settings::Calendar::spaceBetweenCells) / 7, cellHeight = (dcHeight - 5 * Settings::Calendar::spaceBetweenRows) / 6;

	const uint8_t widthLoss = (dcWidth - 6 * Settings::Calendar::spaceBetweenCells) % 7;



	Resources::Calendar::Cell::loadBackground(cellWidth, cellHeight, Settings::Calendar::Cell::monthColors[0]);

	for (uint8_t row = 0; row < 6; row++)
		for (uint8_t cell = 0; cell < 7; cell++) {
			gui::TextArea text(std::to_string(date.getDay()), Resources::arial, Settings::Calendar::Cell::charSize);

			dateCalendar.add("row" + std::to_string(row) + ": cell" + std::to_string(cell), gui::Button().setTexture(Resources::Calendar::Cell::background)
				.setPosition((cellWidth + Settings::Calendar::spaceBetweenCells) * cell + Settings::MonthView::padding.left + ((cell >= 5) ? widthLoss : 0),
					(cellHeight + Settings::Calendar::spaceBetweenRows) * row + Settings::MonthView::padding.top)
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
	

	const unsigned int viewWidth = dcWidth + Settings::MonthView::padding.left + Settings::MonthView::padding.right,
		viewHeight = dcHeight + Settings::MonthView::padding.top + Settings::MonthView::padding.bottom,
		//viewX = viewWidth / 2 + Settings::Calendar::margin.left + Settings::MainWindow::padding.left - Settings::View::padding.left,
		//viewY = viewHeight + S::padding.top + Settings::MainWindow::padding.top - Settings::View::padding.top;
		viewX = Settings::MainWindow::padding.left + Settings::Calendar::margin.left - Settings::MonthView::padding.left,
		viewY = Settings::MainWindow::padding.top + Settings::Calendar::margin.top - Settings::MonthView::padding.top;


	monthView.setSize(viewWidth, viewHeight);
	monthView.setCenter(viewWidth / 2, viewHeight / 2);
	monthView.setViewport(sf::FloatRect(float(viewX) / Settings::MainWindow::width, float(viewY) / Settings::MainWindow::height, float(viewWidth) / width, float(viewHeight) / height));



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

}


void MainWindow::initialize()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "GIGA-Calendar", sf::Style::None);
	
	window.setVerticalSyncEnabled(true);

	/*
	SlideMonth slideDown(false, windowManager.at("dateCalendar", true));
	slideDown.setDuration(4).setFPS(20);
	*/
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
			default:
				windowManager.input(event);
				break;
			}
		}

		window.clear(Settings::MainWindow::backgroundColor);

		
		window.setView(window.getDefaultView());
		window.draw(windowManager);


		window.setView(monthView);
		window.draw(dateCalendar);

		window.display();
	}
}
