//24L-3017 AQSA EHTESHAM
//24L-3068 ZUHAR FAISAL
//24L-3033 ALIZA VAHIDY
//24L-3075 FATIMA ASIF

#include<iostream>
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <fstream>
#include <string>

using namespace std;
using namespace sf;

enum ScreenType {
	MAIN_SCREEN,
	LOLLYWOOD_SCREEN,
	BOLLYWOOD_SCREEN,
	HOLLYWOOD_SCREEN,
	TIMING_SCREEN
};

int seatcount = 0;
int popcorn_price = 0, nachos_price = 0, soda_price = 0; 
const int ticketprice = 2500;
int totalBill = 0;

string selectedGenre = ""; 
string selectedMovie = "";

bool showWelcomeScreen(RenderWindow& parentwindow)
{
	Texture welcomeTexture;
	if (!welcomeTexture.loadFromFile("assets/images/welcome_screen.jpg"))
	{
		cout << "Error loading welcome image!" << endl;
		return false;
	}

	Sprite welcomeSprite(welcomeTexture);
	welcomeSprite.setPosition(0, 0);
	welcomeSprite.setScale(1.5f, 1.3f);

	RectangleShape continueButton(Vector2f(300, 60));
	continueButton.setFillColor(Color::Green);
	continueButton.setPosition(600, 600);
	continueButton.setOutlineColor(Color::Black);
	continueButton.setOutlineThickness(3);

	Font font;
	if (!font.loadFromFile("assets/fonts/times.ttf"))
	{
		cout << "Error loading font!" << endl;
		return false;
	}

	Text buttonText("Continue", font, 42);
	buttonText.setFillColor(Color::Black);
	FloatRect textBounds = buttonText.getLocalBounds();

	//to center align the text in the box
	buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	buttonText.setPosition(continueButton.getPosition().x + continueButton.getSize().x / 2.0f,
		continueButton.getPosition().y + continueButton.getSize().y / 2.0f);

	while (parentwindow.isOpen())
	{
		Event event;
		while (parentwindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
				return false;

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				FloatRect buttonBounds = continueButton.getGlobalBounds();
				if (buttonBounds.contains(event.mouseButton.x, event.mouseButton.y))
				{
					return true; // Proceed to the next screen
				}
			}
		}

		// Highlight button on hover
		if (continueButton.getGlobalBounds().contains(Mouse::getPosition(parentwindow).x, Mouse::getPosition(parentwindow).y))
			continueButton.setFillColor(Color::Yellow);
		else
			continueButton.setFillColor(Color::Green);

		// Render Welcome Screen
		parentwindow.clear();
		parentwindow.draw(welcomeSprite);
		parentwindow.draw(continueButton);
		parentwindow.draw(buttonText);
		parentwindow.display();
	}

	return false;
}

//generates the payment slip
void payment(RenderWindow& parentwindow) 
{
	
	cout << totalBill << endl;
	int userInput = 0;        
	int change = 0;
	bool isInputGiven = false; // Track if any input has been given
	bool isValidInput = true;  // Track if the input is valid

	// Set up fonts and text
	Font font;
	if (!font.loadFromFile("assets/fonts/BKANT.TTF")) {
		cerr << "Error loading font!" << endl;
		return;
	}
	
	// Text to display genre and movie
	Text genreText("\t\tGenre: " + selectedGenre, font, 28);
	genreText.setStyle(Text::Bold); 
	genreText.setPosition(545, 230);
	genreText.setFillColor(Color(101, 67, 33));

	Text movieText("\t\tMovie: " + selectedMovie, font, 28);
	movieText.setStyle(Text::Bold); 
	movieText.setPosition(545, 260);
	movieText.setFillColor(Color(101, 67, 33)); 

	// Text for total bill
	Text totalText("Total Bill: "+ to_string(totalBill), font, 40);  
	totalText.setStyle(Text::Bold);
	totalText.setPosition(600, 180);
	totalText.setFillColor(Color::Black);

	// Text for user input prompt
	Text userInputText("Enter Payment: ", font, 28);
	userInputText.setPosition(545, 480);
	userInputText.setFillColor(Color::Black);

	// Error message (in red)
	Text rederror("", font, 23); 
	rederror.setPosition(540, 510); 
	rederror.setFillColor(Color::Red); 

	// Text to show change
	Text paymentText("", font, 28);
	paymentText.setPosition(545, 495);
	paymentText.setFillColor(Color::Black);

	// Text to show user input dynamically
	Text inputText("", font, 30);  // Text that shows the user's input
	inputText.setPosition(760, 480);   // Positioning it below the prompt
	inputText.setFillColor(Color::Black);
	
	//seat detail
	Text seatDetail("Tickets Booked:  "+to_string(seatcount)+"\nTickets Bill: Rs."+to_string(ticketprice*seatcount)+
		"\nPopcorns Bill : Rs."+to_string(popcorn_price)+
		"\nNachos Bill:  Rs."+to_string(nachos_price)+"\nSoda Bill:  Rs."+to_string(soda_price), font, 26); 
	seatDetail.setPosition(545, 300);  
	seatDetail.setFillColor(Color(128, 128, 128));

	Text thankyouText("Thank you for choosing \n        Fast Cine Hive!", font, 30);
	thankyouText.setStyle(Text::Bold);
	thankyouText.setPosition(555, 650); 
	thankyouText.setFillColor(Color::Black); 

	Text storyText("Your ticket to unforgettable stories \nhas been stamped.", font, 22);
	storyText.setStyle(Text::Italic);
	storyText.setPosition(545, 570);
	storyText.setFillColor(Color::Magenta);  

	// Create a lavender circle for the background
	CircleShape circle(400);
	circle.setFillColor(Color(230, 230, 250));  // Lavender color with RGB values
	circle.setPosition(350, 60); // Position the circle behind the rectangle

	// Create a white rectangle in the front
	RectangleShape rectangle(Vector2f(500, 620));  // A large white rectangle
	rectangle.setFillColor(Color::White);
	rectangle.setPosition(500, 150); // Position the rectangle in front of the circle

	// Variable for handling user input
	bool validInput = false;
	ofstream outpayment("assets/data/paymentslip.txt", ios:: app);
	if (!outpayment.is_open())
	{
		cerr << "Error opening file for writing " << endl;
		return;
	}

	while (parentwindow.isOpen())
	{
		Event event;
		while (parentwindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				parentwindow.close();
				outpayment.close();
			}

			// Handling key press for numbers and backspace
			if (event.type == Event::KeyPressed)
			{
				//checks user enters between 0 and 9
				if (event.key.code >= Keyboard::Num0 && event.key.code <= Keyboard::Num9)
				{
					// Append the digit to userInput (convert the keycode to digit)
					userInput = userInput * 10 + (event.key.code - Keyboard::Num0);
					isInputGiven = true; // Mark that the user has given some input
				}
				else if (event.key.code == Keyboard::BackSpace)
				{
					// Handle backspace (remove last digit)
					userInput /= 10;
					if (userInput == 0)
					{
						isInputGiven = false; // Reset the flag if no input is left
					}
				}
				else if (event.key.code == Keyboard::Return)
				{
					// Check input when Enter is pressed
					if (userInput < totalBill) {
						// Invalid input, show error
						isValidInput = false;
						rederror.setString("Amount is less than the bill. Try again."); 
						paymentText.setString(""); // Clear the previous payment details
					}
					else
					{
						// Valid input, proceed
						isValidInput = true;
						change = userInput - totalBill;
						paymentText.setString("\nChange: Rs." + to_string(change));
						outpayment << "Total Bill is : " << totalBill << endl;
						outpayment << "Payment received is : " << userInput << endl;
						outpayment << "Change returned is : " << change << endl;
						outpayment << "<------------------------------------>" << endl;
						outpayment.close();
					}

					// Reset the input if invalid, allow user to try again
					if (!isValidInput)
					{
						userInput = 0; // Reset the user input
					}
				}
			}
		}

		// Update inputText to show the current user input as a string
		inputText.setString(to_string(userInput));

		// Drawing
		parentwindow.clear(Color::White); // Clear the window with white color

		// Draw background circle and rectangle
		parentwindow.draw(circle);
		parentwindow.draw(rectangle);

		// Draw text (bill, error, and payment info)
		parentwindow.draw(totalText);
		parentwindow.draw(userInputText);
		parentwindow.draw(seatDetail); 
		parentwindow.draw(thankyouText);
		parentwindow.draw(storyText);
		parentwindow.draw(inputText); 
		
		parentwindow.draw(genreText); 
		parentwindow.draw(movieText); 
		parentwindow.draw(rederror); 
		if (isValidInput)
		{
			parentwindow.draw(paymentText);  // Draw payment and change if valid
		}

		parentwindow.display(); // Display everything on the screen
	}
}
void selectSnacks(RenderWindow& parentwindow)
{
	int popcorncount = 0, nachoscount = 0, sodacount = 0; 
	// Images of snacks
	Texture popcornTexture, nachosTexture, sodaTexture;
	if (!popcornTexture.loadFromFile("assets/images/popcorn.jpg") ||
		!nachosTexture.loadFromFile("assets/images/nachos.jpg") ||
		!sodaTexture.loadFromFile("assets/images/soda.jpg"))
	{
		cerr << "Error loading snack images!" << endl;
		return;
	}

	Sprite popcornSprite(popcornTexture), nachosSprite(nachosTexture), sodaSprite(sodaTexture);

	// Setting positions for the images
	popcornSprite.setPosition(0, 270);
	nachosSprite.setPosition(500, 270);
	sodaSprite.setPosition(1000, 270);

	popcornSprite.setScale(1.2f, 1.0f);
	nachosSprite.setScale(0.9f, 0.7f);
	sodaSprite.setScale(1.5f, 1.2f);

	// Snack names and prices
	string snackNames[3] = { "Popcorn", "Nachos", "Soda" };
	int snackPrices[3] = { 499, 699, 299 }; // Prices for Popcorn, Nachos, and Soda
	int snackQuantities[3] = { 0, 0, 0 }; // Quantities for each snack, initialized to 0

	// Create the "Continue" button
	RectangleShape continueButton(Vector2f(200, 50));
	continueButton.setFillColor(Color::Green);
	continueButton.setPosition(650, 740);
	continueButton.setOutlineColor(Color::Black);
	continueButton.setOutlineThickness(3);

	Font font;
	if (!font.loadFromFile("assets/fonts/arial.ttf"))
	{
		cerr << "Error loading font!" << endl;
		return;
	}
	Text continueText("Continue", font, 26);
	continueText.setFillColor(Color::White);
	//to align the text in the rectangle
	continueText.setPosition(continueButton.getPosition().x + 50, continueButton.getPosition().y + 10);

	Font selectsnack;
	if (!selectsnack.loadFromFile("assets/fonts/BKANT.TTF"))
	{
		cerr << "Error loading font!" << endl;
		return;
	}
	Text selectsnackHeading("Press On Your Favourite Snack to Choose: ", selectsnack, 55);
	selectsnackHeading.setFillColor(Color::White);
	selectsnackHeading.setPosition(260, 150);

	ofstream outfile("assets/data/Snacks.txt", ios::app); // Open in append mode
	if (!outfile.is_open()) 
	{
		cerr << "Error opening file for writing!" << endl;
		return;
	}
	while (parentwindow.isOpen())
	{
		Event event;
		while (parentwindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				parentwindow.close();
				outfile.close();
				return;
			}

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					// Check if user clicked on a snack image to select quantity
					if (popcornSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						snackQuantities[0]++; 
						popcorncount++;
					}
					else if (nachosSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						snackQuantities[1]++; 
						nachoscount++;
					}
					else if (sodaSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						snackQuantities[2]++; 
						sodacount++; 
					}
					
					// Check if "Continue" button is pressed to go to the bill window
					if (continueButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						// Write final quantities to the file
						outfile << "Snack Selection Summary:\n";
						outfile << snackNames[0] << ": " << snackQuantities[0] << " @ Rs. " << snackPrices[0] << " each\n";
						outfile << snackNames[1] << ": " << snackQuantities[1] << " @ Rs. " << snackPrices[1] << " each\n";
						outfile << snackNames[2] << ": " << snackQuantities[2] << " @ Rs. " << snackPrices[2] << " each\n";
						outfile << "------------------------\n";

						//calculating snacks prices 
						popcorn_price = popcorncount * 499;
						nachos_price = nachoscount * 699;
						soda_price = sodacount * 299;

						int snackbill = popcorn_price + nachos_price + soda_price;
						cout << "Snacks bill: " <<snackbill<< endl;
						outfile<< "Snacks bill: " << snackbill<<endl;
						totalBill = totalBill + snackbill;
						outfile.close();
						payment(parentwindow); // Set flag to transition to payment screen
						return; //to exit the snacks window
					}
				}
			}
		}
	
		parentwindow.clear();
		// Draw the snack images
		parentwindow.draw(popcornSprite);
		parentwindow.draw(nachosSprite);
		parentwindow.draw(sodaSprite);

		// Draw the snack names and prices
		Text snackText1(snackNames[0] + " - Rs." + to_string(snackPrices[0]), font, 24);
		snackText1.setPosition(100, 650);
		parentwindow.draw(snackText1);

		Text snackText2(snackNames[1] + " - Rs. " + to_string(snackPrices[1]), font, 24);
		snackText2.setPosition(600, 650);
		parentwindow.draw(snackText2);

		Text snackText3(snackNames[2] + " - Rs. " + to_string(snackPrices[2]), font, 24);
		snackText3.setPosition(1080, 650);
		parentwindow.draw(snackText3);

		// Draw quantities for each snack
		Text quantityText1("Qty: " + to_string(snackQuantities[0]), font, 24);
		quantityText1.setPosition(100, 700);
		parentwindow.draw(quantityText1);

		Text quantityText2("Qty: " + to_string(snackQuantities[1]), font, 24);
		quantityText2.setPosition(600, 700);
		parentwindow.draw(quantityText2);

		Text quantityText3("Qty: " + to_string(snackQuantities[2]), font, 24);
		quantityText3.setPosition(1080, 700);
		parentwindow.draw(quantityText3);

		// Draw continue button and text
		parentwindow.draw(continueButton);
		parentwindow.draw(continueText);

		parentwindow.draw(selectsnackHeading);
		parentwindow.display();
	}
	
	
}

//for seating arrangment
void seatingArrangement(RenderWindow& parentWindow)
{
	const int rows = 5;   // Number of rows
	const int cols = 5;  // Number of columns
	int seats[rows][cols] = { 0 };  // 0 = available, 1 = booked

	Font selectseat;
	if (!selectseat.loadFromFile("assets/fonts/BKANT.TTF"))
	{
		cerr << "Error loading font!" << endl;
		return;
	}
	Text selectseatHeading("Press On the Seat to Choose: ", selectseat, 55);
	selectseatHeading.setFillColor(Color::White);
	selectseatHeading.setPosition(450, 100);

	Font seatFont;
	if (!seatFont.loadFromFile("assets/fonts/arial.ttf"))
	{
		cout << "Error loading font!" << endl;
		return;
	}

	Text confirmButton("CONFIRM", seatFont, 30);
	confirmButton.setFillColor(Color::White);
	confirmButton.setPosition(1220, 755);

	// Load images for available and booked seats
	Texture availableSeatTexture;
	if (!availableSeatTexture.loadFromFile("assets/images/seat_available.png"))
	{
		cout << "Error loading seat_available.png!" << endl;
		return;
	}

	Texture bookedSeatTexture;
	if (!bookedSeatTexture.loadFromFile("assets/images/seat_booked.png"))
	{
		cout << "Error loading seat_booked.png!" << endl;
		return;
	}

	// Scale the seat images to fit the grid
	Sprite availableSeatSprite(availableSeatTexture);
	Sprite bookedSeatSprite(bookedSeatTexture);

	availableSeatSprite.setScale(0.09f, 0.08f); // Adjust scale as per image size
	bookedSeatSprite.setScale(0.17f, 0.17f);    // Adjust scale as per image size
	ofstream outseat("assets/data/seatfile.txt", ios::app);
	if (!outseat.is_open()) {
		cerr << "Error opening file for writing!" << endl;
		return;
	}

	while (parentWindow.isOpen())
	{
		Event event;
		while (parentWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				parentWindow.close();
				outseat.close(); // Ensure file is closed when the window is closed
				return;
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				//// Get the mouse position relative to the window
				int mouseX = event.mouseButton.x;
				int mouseY = event.mouseButton.y;

				// Check for seat selection
				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < cols; j++)
					{
						FloatRect seatBounds(
							j * (availableSeatSprite.getGlobalBounds().width + 10) + 500,
							i * (availableSeatSprite.getGlobalBounds().height + 10) + 230,
							availableSeatSprite.getGlobalBounds().width,
							availableSeatSprite.getGlobalBounds().height
						);

						if (seatBounds.contains(mouseX, mouseY))
						{
							
							if (seats[i][j] == 0)  // If seat is available
							{
								seatcount++; 
								seats[i][j] = 1;  // Mark the seat as booked
							}
						}
					}
				}

				// Check if "CONFIRM" button is clicked
				RectangleShape confirmRect(Vector2f(180, 55));
				confirmRect.setPosition(1200, 750);

				// Check if "Confirm" button is clicked
				if (confirmButton.getGlobalBounds().contains(mouseX, mouseY))
				{
					cout << "Seats confirmed!" << endl;
					outseat << "Final Seat Arrangement:\n";
					for (int i = 0; i < rows; i++)
					{
						for (int j = 0; j < cols; j++)
						{
						outseat<< (seats[i][j] == 1 ? "X" : "O") << " ";
						}
					outseat << "\n";
					}
				   outseat << "------------------------\n";
					outseat.close();
					totalBill = totalBill + (seatcount * ticketprice);
					selectSnacks(parentWindow);
					return; //to exit the seating window
				}
			}
		}

		// Rendering
		parentWindow.clear();

		// Draw seats
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				int gap = 10;
				Sprite seatSprite;
				if (seats[i][j] == 0)
				{
					seatSprite = availableSeatSprite;
				}
				else
				{
					seatSprite = bookedSeatSprite;  // Use the booked seat texture 
				}
				//to handle gap between the seats
				seatSprite.setPosition(j * (100 + gap) + 500, i * (100 + gap) + 230);
				parentWindow.draw(seatSprite);
			}
		}

		// Draw confirm button
		RectangleShape confirmRect(Vector2f(180, 55));
		confirmRect.setPosition(1200, 750);
		confirmRect.setFillColor(Color::Blue);
		parentWindow.draw(confirmRect);
		parentWindow.draw(confirmButton);
		parentWindow.draw(selectseatHeading);

		parentWindow.display();
	}
	
}


void selectTiming(RenderWindow& parentwindow)
{
	Texture timetexture;

	if (!timetexture.loadFromFile("assets/images/movietime.jpg"))
	{
		cerr << "Error loading image!" << endl;
		return;
	}

	Sprite timeSprite(timetexture);
	timeSprite.setPosition(0, 50);
	timeSprite.setScale(5.0f, 1.5f);

	// Load font
	Font timefont;
	if (!timefont.loadFromFile("assets/fonts/BKANT.TTF"))
	{
		cerr << "Error loading font!" << endl;
		return;
	}

	// Create heading text
	Text heading("Please select a showtime:", timefont, 50);
	heading.setFillColor(Color::White);
	heading.setPosition(450, 340);

	// Create buttons for timings
	RectangleShape buttons[3];
	Text buttonTexts[3];

	string timings[] = { "10:00 AM", " 3:00 PM", " 8:00 PM" }; // Replace with your timings array
	for (int i = 0; i < 3; i++) {
		buttons[i].setSize(Vector2f(300, 60));
		buttons[i].setPosition(600, 460 + i * 100);
		buttons[i].setFillColor(Color::Red);

		buttonTexts[i].setFont(timefont);
		buttonTexts[i].setString(timings[i]);
		buttonTexts[i].setCharacterSize(30);
		buttonTexts[i].setFillColor(Color::White);
		buttonTexts[i].setPosition(690, 470 + i * 100);
	}

	bool proceedToSeating = false;
	ofstream outtiming("assets/data/Time.txt", ios::app);
	if (!outtiming.is_open())
	{
		cerr << "Error opening file for writing!" << endl;
		return;
	}

	// Event loop
	while (parentwindow.isOpen())
	{
		Event event;
		while (parentwindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				parentwindow.close();
				outtiming.close();
				return;
			}

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					for (int i = 0; i < 3; i++)
					{
						if (buttons[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
						{
							outtiming << "Selected Showtime: " << timings[i] << endl;
							outtiming.close();
							seatingArrangement(parentwindow);
							
							proceedToSeating = true; // Flag to move to seating arrangement
							return;
						}
					}
				}
			}
		}

		// Render the UI
		parentwindow.clear();
		parentwindow.draw(heading);
		parentwindow.draw(timeSprite);
		for (int i = 0; i < 3; i++)
		{
			parentwindow.draw(buttons[i]);
			parentwindow.draw(buttonTexts[i]);
		}
		parentwindow.display();
	}

	return; // If window closes unexpectedly
}

void genreSelection(RenderWindow& parentwindow, int& currentScreen)
{
	const int GENRE = 0;
	const int LOLLYWOOD = 1;
	const int BOLLYWOOD = 2;
	const int HOLLYWOOD = 3;

	currentScreen = GENRE;
	ScreenType current = MAIN_SCREEN;

	if (currentScreen == GENRE)
	{
		Texture lollywoodtexture, bollywoodtexture, hollywoodtexture;

		if (!lollywoodtexture.loadFromFile("assets/images/lollywood.jpg") ||
			!bollywoodtexture.loadFromFile("assets/images/bollywood.jpg") ||
			!hollywoodtexture.loadFromFile("assets/images/hollywood.jpg"))
		{
			cout << "Error loading image!" << endl;
			return;
		}

		Sprite lollywoodSprite(lollywoodtexture);
		Sprite bollywoodSprite(bollywoodtexture);
		Sprite hollywoodSprite(hollywoodtexture);

		// Set positions for the category images
		lollywoodSprite.setPosition(0, 400);
		bollywoodSprite.setPosition(450, 400);
		hollywoodSprite.setPosition(950, 400);

		lollywoodSprite.setScale(2.0f, 1.4f);
		bollywoodSprite.setScale(0.9f, 0.6f);
		hollywoodSprite.setScale(0.3f, 0.2f);


		// Create category heading text
		Font categoryFont;
		if (!categoryFont.loadFromFile("assets/fonts/times.ttf"))
		{
			cout << "Error loading font!" << endl;
			return;
		}
		Text categoryHeading("CATEGORIES ", categoryFont, 65);  // Heading font size: 40px
		categoryHeading.setFillColor(Color::White);
		categoryHeading.setPosition(550, 190);  // Position the heading at the top

		Font selectgenre;
		if (!selectgenre.loadFromFile("assets/fonts/BKANT.TTF"))
		{
			cout << "Error loading font!" << endl;
			return;
		}
		Text selectHeading("Click on any one of the following: ", selectgenre, 40);  // Heading font size: 40px
		selectHeading.setFillColor(Color::White);
		selectHeading.setPosition(240, 270);  // Position the heading at the top 
		ofstream outgenre("assets/data/Genre.txt", ios::app);
		if (!outgenre.is_open())
		{
			cerr << "Error opening file for writing!" << endl;
			return;
		}
		while (parentwindow.isOpen())
		{
			Event event;
			while (parentwindow.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					
					parentwindow.close();
					outgenre.close();
					return;
				}
				//for getting mouse coordinates
				Vector2f mousePos = parentwindow.mapPixelToCoords(Mouse::getPosition(parentwindow));
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
				{
					if (lollywoodSprite.getGlobalBounds().contains(mousePos))
					{
						cout << "Lollywood clicked!" << endl;
						selectedGenre = "Lollywood"; 
						outgenre << "Lollywood clicked!" << endl;
						currentScreen = LOLLYWOOD;
						Texture punjabtexture, maulatexture, jawanitexture;

						if (!punjabtexture.loadFromFile("assets/images/punjab.jpg") ||
							!maulatexture.loadFromFile("assets/images/maula.jpg") ||
							!jawanitexture.loadFromFile("assets/images/jawani.jpg"))
						{
							cout << "Error loading image!" << endl;
							return;
						}

						Sprite punjabSprite(punjabtexture);
						Sprite maulaSprite(maulatexture);
						Sprite jawaniSprite(jawanitexture);

						punjabSprite.setPosition(0, 230);
						maulaSprite.setPosition(525, 230);
						jawaniSprite.setPosition(1030, 230);

						punjabSprite.setScale(0.5f, 0.6f);
						maulaSprite.setScale(0.6f, 0.6f);
						jawaniSprite.setScale(1.0f, 1.2f);


						// Create category heading text
						Font lollyFont;
						if (!lollyFont.loadFromFile("assets/fonts/times.ttf"))
						{
							cout << "Error loading font!" << endl;
							return;
						}
						Text lollyHeading("Lights, Camera, Action! ", lollyFont, 46);  // Heading font size: 40px
						lollyHeading.setFillColor(Color::White);
						lollyHeading.setPosition(550, 120);
						Font lollyselectFont;
						if (!lollyselectFont.loadFromFile("assets/fonts/BKANT.TTF"))
						{
							cout << "Error loading font!" << endl;
							return;
						}
						Text lollyselectHeading("Select your Film and Let the Entertainment Ignite", lollyselectFont, 35);  // Heading font size: 40px
						lollyselectHeading.setFillColor(Color::White);
						lollyselectHeading.setPosition(370, 180);
						while (parentwindow.isOpen())
						{
							Event event;
							while (parentwindow.pollEvent(event))
							{
								if (event.type == Event::Closed)
								{
									parentwindow.close();
								}

								if (current == MAIN_SCREEN)
								{
									Vector2f mousePos = parentwindow.mapPixelToCoords(Mouse::getPosition(parentwindow));
									if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
										if (lollywoodSprite.getGlobalBounds().contains(mousePos)) {
											current = LOLLYWOOD_SCREEN; // Switch to Lollywood
										}
										else if (bollywoodSprite.getGlobalBounds().contains(mousePos)) {
											current = BOLLYWOOD_SCREEN; // Switch to Bollywood
										}
										else if (hollywoodSprite.getGlobalBounds().contains(mousePos)) {
											current = HOLLYWOOD_SCREEN; // Switch to Hollywood
										}
									}
								}
								else if (current == LOLLYWOOD_SCREEN) {
									Vector2f mousePos = parentwindow.mapPixelToCoords(Mouse::getPosition(parentwindow));
									if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) 
									{
										if (punjabSprite.getGlobalBounds().contains(mousePos))
										{
											selectedMovie = "Punjab Nahi Jaungi";
											cout << "Punjab Nahi Jaungi selected : " << endl;
											outgenre<<"Punjab Nahi Jaungi selected : " << endl;
										}
										else if (maulaSprite.getGlobalBounds().contains(mousePos))
										{
											selectedMovie = "Maula Jatt";
											cout << "Maula Jatt selected : " << endl;
											outgenre << "Maula Jatt selected : " << endl;
										}
										else if (jawaniSprite.getGlobalBounds().contains(mousePos))
										{
											selectedMovie = "Jawani Phir Nahi Ani";
											cout << "Jawani Phir Nahi Ani selected : " << endl;
											outgenre << "Jawani Phir Nahi Ani selected : " << endl;
										}
											selectTiming(parentwindow);
											return;
									}
								}
							}

							// Render screen based on current state
							parentwindow.clear();

							if (current == MAIN_SCREEN) {
								parentwindow.draw(lollywoodSprite);
								parentwindow.draw(bollywoodSprite);
								parentwindow.draw(hollywoodSprite);
							}
							else if (current == LOLLYWOOD_SCREEN) {
								parentwindow.draw(punjabSprite);
								parentwindow.draw(maulaSprite);
								parentwindow.draw(jawaniSprite); 
								parentwindow.draw(lollyHeading); 
								parentwindow.draw(lollyselectHeading); 
							}

							parentwindow.display();
						}
					}
					else if (bollywoodSprite.getGlobalBounds().contains(mousePos))
					{
						selectedGenre = "Bollywood"; 
						cout << "Bollywood clicked!" << endl;
						outgenre << "Bollywood clicked!" << endl;
						currentScreen = BOLLYWOOD;
						Texture idiottexture, dangaltexture, sholaytexture;

						if (!idiottexture.loadFromFile("assets/images/idiots.jpg") ||
							!dangaltexture.loadFromFile("assets/images/dangal.jpg") ||
							!sholaytexture.loadFromFile("assets/images/sholay.jpg"))
						{
							cout << "Error loading image!" << endl;
							return;
						}

						Sprite idiotSprite(idiottexture);
						Sprite dangalSprite(dangaltexture);
						Sprite sholaySprite(sholaytexture);

						idiotSprite.setPosition(0, 230);
						dangalSprite.setPosition(535, 230);
						sholaySprite.setPosition(1010, 230);

						idiotSprite.setScale(0.33f, 0.35f);
						dangalSprite.setScale(0.23f, 0.25f);
						sholaySprite.setScale(0.62f, 0.7f);

						Font bollyFont;
						if (!bollyFont.loadFromFile("assets/fonts/times.ttf"))
						{
							cout << "Error loading font!" << endl;
							return;
						}
						Text bollyHeading("Lights, Camera, Action! ", bollyFont, 46);  // Heading font size: 40px
						bollyHeading.setFillColor(Color::White);
						bollyHeading.setPosition(550, 120);
						Font bollyselectFont;
						if (!bollyselectFont.loadFromFile("assets/fonts/BKANT.TTF"))
						{
							cout << "Error loading font!" << endl;
							return;
						}

						while (parentwindow.isOpen())
						{
							Event bollyEvent;
							while (parentwindow.pollEvent(bollyEvent))
							{
								if (bollyEvent.type == Event::Closed)
									parentwindow.close();
								
								if (current == MAIN_SCREEN) {
									Vector2f mousePos = parentwindow.mapPixelToCoords(Mouse::getPosition(parentwindow));
									if (bollyEvent.type == Event::MouseButtonReleased && bollyEvent.mouseButton.button == Mouse::Left) {
										if (lollywoodSprite.getGlobalBounds().contains(mousePos)) {
											current = LOLLYWOOD_SCREEN; // Switch to Lollywood
										}
										else if (bollywoodSprite.getGlobalBounds().contains(mousePos)) {
											current = BOLLYWOOD_SCREEN; // Switch to Bollywood
										}
										else if (hollywoodSprite.getGlobalBounds().contains(mousePos)) {
											current = HOLLYWOOD_SCREEN; // Switch to Hollywood
										}
									}
								}
								else if (current == BOLLYWOOD_SCREEN) 
								{
									Vector2f mousePos = parentwindow.mapPixelToCoords(Mouse::getPosition(parentwindow));
									if (bollyEvent.type == Event::MouseButtonReleased && bollyEvent.mouseButton.button == Mouse::Left) 
									{
										
										if (idiotSprite.getGlobalBounds().contains(mousePos))
										{
											selectedMovie = "3 Idiots";
											cout << "3 Idiots selected: " << endl;
											outgenre << "3 Idiots selected: " << endl;
										}
										else if (dangalSprite.getGlobalBounds().contains(mousePos))
										{
											selectedMovie = "Dangal";
											cout << "Dangal selected: " << endl;
											outgenre << "Dangal selected: " << endl;
										}
										else if (sholaySprite.getGlobalBounds().contains(mousePos))
										{
											selectedMovie = "Sholay";
											cout << "Sholay selected: " << endl;
											outgenre << "Sholay selected: " << endl;
										}
											selectTiming(parentwindow);
											return;
										
									}
								}
							}
							
							parentwindow.clear();

							if (current == MAIN_SCREEN) {
								parentwindow.draw(lollywoodSprite);
								parentwindow.draw(bollywoodSprite);
								parentwindow.draw(hollywoodSprite);
							}
							else if (current == BOLLYWOOD_SCREEN) {
								Text bollyselectHeading("Select your Film and Let the Entertainment Ignite", bollyselectFont, 35);  // Heading font size: 40px
								bollyselectHeading.setFillColor(Color::White);
								bollyselectHeading.setPosition(370, 180);
								parentwindow.draw(idiotSprite);
								parentwindow.draw(dangalSprite);
								parentwindow.draw(sholaySprite);
								parentwindow.draw(bollyHeading);
								parentwindow.draw(bollyselectHeading);
							}

							parentwindow.display();
						}
					}
					else if (hollywoodSprite.getGlobalBounds().contains(mousePos))
					{
						selectedGenre = "Hollywood";
						cout << "Hollywood clicked!" << endl;
						outgenre<< "Hollywood clicked!" << endl;
						currentScreen = HOLLYWOOD;
						Texture avengerstexture, inceptiontexture, titanictexture;

						if (!avengerstexture.loadFromFile("assets/images/avengers.jpg") ||
							!inceptiontexture.loadFromFile("assets/images/inception.jpg") ||
							!titanictexture.loadFromFile("assets/images/titanic.jpg"))
						{
							cout << "Error loading image!" << endl;
							return;
						}

						Sprite avengersSprite(avengerstexture);
						Sprite inceptionSprite(inceptiontexture);
						Sprite titanicSprite(titanictexture);

						avengersSprite.setPosition(0, 230);
						inceptionSprite.setPosition(530, 230);
						titanicSprite.setPosition(1010, 230);

						avengersSprite.setScale(0.6f, 0.6f);
						inceptionSprite.setScale(0.4f, 0.4f);
						titanicSprite.setScale(0.35f, 0.5f);

						Font hollyFont;
						if (!hollyFont.loadFromFile("assets/fonts/times.ttf"))
						{
							cout << "Error loading font!" << endl;
							return;
						}
						Text hollyHeading("Lights, Camera, Action! ", hollyFont, 46);  // Heading font size: 40px
						hollyHeading.setFillColor(Color::White);
						hollyHeading.setPosition(550, 120);
						Font hollyselectFont;
						if (!hollyselectFont.loadFromFile("assets/fonts/BKANT.TTF"))
						{
							cout << "Error loading font!" << endl;
							return;
						}

						while (parentwindow.isOpen())
						{
							Event hollyEvent;
							while (parentwindow.pollEvent(hollyEvent))
							{
								if (hollyEvent.type == Event::Closed)
									parentwindow.close();
								if (current == MAIN_SCREEN) {
									Vector2f mousePos = parentwindow.mapPixelToCoords(Mouse::getPosition(parentwindow));
									if (hollyEvent.type == Event::MouseButtonReleased && hollyEvent.mouseButton.button == Mouse::Left) {
										if (lollywoodSprite.getGlobalBounds().contains(mousePos)) {
											current = LOLLYWOOD_SCREEN; // Switch to Lollywood
										}
										else if (bollywoodSprite.getGlobalBounds().contains(mousePos)) {
											current = BOLLYWOOD_SCREEN; // Switch to Bollywood
										}
										else if (hollywoodSprite.getGlobalBounds().contains(mousePos)) {
											current = HOLLYWOOD_SCREEN; // Switch to Hollywood
										}
									}
								}
								else if (current == HOLLYWOOD_SCREEN) {
									Vector2f mousePos = parentwindow.mapPixelToCoords(Mouse::getPosition(parentwindow));
									if (hollyEvent.type == Event::MouseButtonReleased && hollyEvent.mouseButton.button == Mouse::Left) 
									{
										if (avengersSprite.getGlobalBounds().contains(mousePos))
										{
											selectedMovie = "Avengers";
											cout << "Avengers selected :" << endl;
											outgenre << "Avengers selected :" << endl;

										}
										else if (inceptionSprite.getGlobalBounds().contains(mousePos))
										{
											selectedMovie = "Inception";
											cout << "Inception selected :" << endl;
											outgenre << "Inception selected :" << endl;
										}
										else if (titanicSprite.getGlobalBounds().contains(mousePos))
										{
											selectedMovie = "Titanic"; 
											cout << "Titanic selected :" << endl;
											outgenre << "Titanic selected :" << endl;
											outgenre.close();
										}
											selectTiming(parentwindow);
											return;
										
									}
								}
							}
							parentwindow.clear();

							if (current == MAIN_SCREEN) {
								parentwindow.draw(lollywoodSprite);
								parentwindow.draw(bollywoodSprite);
								parentwindow.draw(hollywoodSprite);
							}
							else if (current == HOLLYWOOD_SCREEN) {
								Text hollyselectHeading("Select your Film and Let the Entertainment Ignite", hollyselectFont, 35);  // Heading font size: 40px
								hollyselectHeading.setFillColor(Color::White);
								hollyselectHeading.setPosition(370, 180);
								parentwindow.draw(avengersSprite);
								parentwindow.draw(inceptionSprite);
								parentwindow.draw(titanicSprite);
								parentwindow.draw(hollyHeading);
								parentwindow.draw(hollyselectHeading);
							}

							parentwindow.display();
						}
					}
				}
			}
			parentwindow.clear();
			parentwindow.draw(lollywoodSprite);
			parentwindow.draw(bollywoodSprite);
			parentwindow.draw(hollywoodSprite);
			parentwindow.draw(categoryHeading);
			parentwindow.draw(selectHeading);
			parentwindow.display();
		}
	}
}


int main()
{
	Music backgroundmusic;
	if (!backgroundmusic.openFromFile("assets/audio/backgroundmusic.mp3"))
	{
		cerr << "Could not load background music file" << endl;
		return -1;
	}

	// Set the music to loop
	backgroundmusic.setLoop(true);

	// Play the music (this is done once)
	backgroundmusic.play();

	RenderWindow mainWindow(VideoMode(1500, 1000), "Cinema Reservation System");

	// Show Welcome Screen
	if (!showWelcomeScreen(mainWindow))
	{
		cout << "Exiting program from Welcome Screen!" << endl;
		return 0;
	}

	int currentScreen = 0; // Define and initialize the variable
	// Genre Selection Screen

	bool proceedToTime = false;
	bool proceedToSeating = false;
	bool proceedToSnacks = false;
	bool proceedToPayment = false;
	genreSelection(mainWindow, currentScreen);
	
	while (mainWindow.isOpen())
	{
		Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
				mainWindow.close();
		}

		if (!proceedToTime)
			selectTiming(mainWindow);
	}

	cout << "Total Bill: " << totalBill << endl;

	// Main game/rendering logic here
	mainWindow.clear();
	mainWindow.display();
	return 0;
}
