#pragma once
#include "map.h"
#include "MapWrapper.h"
#include <msclr/marshal_cppstd.h>
#include <msclr/marshal.h>
#include <string>
#include <sstream>
#include <chrono>



namespace NAGGui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	

	using namespace msclr::interop;

	
	/// <summary>
	/// Summary for Window
	/// </summary>
	/// 
	/// 
	public ref class Window : public System::Windows::Forms::Form
	{

	public:

		Window(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here

			mapper = gcnew MapWrapper();

			// Set the form's background to a circular gradient
			this->BackgroundImage = gcnew System::Drawing::Bitmap(this->Width, this->Height);
			System::Drawing::Graphics^ graphics = System::Drawing::Graphics::FromImage(this->BackgroundImage);
			System::Drawing::RectangleF rect = System::Drawing::RectangleF(0, 0, this->Width, this->Height);
			System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();
			path->AddEllipse(rect);
			System::Drawing::Drawing2D::PathGradientBrush^ brush = gcnew System::Drawing::Drawing2D::PathGradientBrush(path);
			brush->CenterPoint = System::Drawing::PointF(this->Width / 2.0f, this->Height / 2.0f);
			brush->CenterColor = System::Drawing::Color::LightBlue;
			brush->SurroundColors = gcnew array<System::Drawing::Color>{ System::Drawing::Color::DarkBlue };
			graphics->FillRectangle(brush, rect);

			
			pictureBox1->SendToBack();
			pictureBox2->SendToBack();
			Title->SendToBack();

			//GENDER BOX DROP DOWN
			ArrayList^ genderList = gcnew ArrayList();
			genderList->Add("Female");
			genderList->Add("Male");

			// Add the items from the ArrayList to the combo box
			for each (String ^ gender in genderList)
			{
				GenderBox->Items->Add(gender);
			}

			// Set the default selected item
			GenderBox->SelectedIndex = 0;

			//Make state check box
			array<String^>^ stateArray = gcnew array<String^> { "Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado", "Connecticut", "D.C.", "Delaware", "Florida", "Georgia", "Hawaii", 
				"Idaho", "Illinois", "Indiana", "Iowa", "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland", "Massachusetts", "Michigan", "Minnesota", "Mississippi", "Missouri", "Montana", 
				"Nebraska", "Nevada", "New Hampshire", "New Jersey", "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio", "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island", 
				"South Carolina", "South Dakota", "Tennessee", "Texas", "Utah", "Vermont", "Virginia", "Washington", "West Virginia", "Wisconsin", "Wyoming" };


			/*array<String^>^ stateArray = gcnew array<String^>{
				"AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DC", "DE", "FL", "GA", "HI",
					"ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD", "MA", "MI", "MN",
					"MS", "MO", "MT", "NE", "NV", "NH", "NJ", "NM", "NY", "NC", "ND", "OH",
					"OK", "OR", "PA", "RI", "SC", "SD", "TN", "TX", "UT", "VT", "VA", "WA",
					"WV", "WI", "WY"
			};*/

			for each (String ^ state in stateArray)
			{
				StateBox->Items->Add(state);
			}

			//Sort Options
			ArrayList^ sortTypeArrayList = gcnew ArrayList();
			sortTypeArrayList->Add("Merge Sort");
			sortTypeArrayList->Add("Quick Sort");
			sortTypeArrayList->Add("Comb Sort");
			sortTypeArrayList->Add("Tim Sort");

			// Add the items from the ArrayList to the combo box
			for each (String ^ sortType in sortTypeArrayList)
			{
				SortTypeDropDown->Items->Add(sortType);
			}

			// Set the default selected item
			SortTypeDropDown->SelectedIndex = 0;

			//BOTTOM TEN ROWS
			int labelHeight_Bottom = BottomTen->Height / 10;

			// Add ten labels to the panel
			for (int i = 1; i <= 10; i++)
			{
				Label^ label = gcnew Label();
				label->Name = "uniquityLabel" + i;
				label->Text = "-";
				label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				label->AutoSize = false;
				label->Width = BottomTen->Width;
				label->Height = labelHeight_Bottom;
				label->Top = (i - 1) * labelHeight_Bottom;
				BottomTen->Controls->Add(label);
			}

			//TOP TEN ROWS
			int labelHeight_Top = TopTen->Height / 10;

			// Add ten labels to the panel
			for (int i = 1; i <= 10; i++)
			{
				Label^ label = gcnew Label();
				label->Name = "commonLabel" + i;
				label->Text = "-";
				label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				label->AutoSize = false;
				label->Width = TopTen->Width;
				label->Height = labelHeight_Top;
				label->Top = (i - 1) * labelHeight_Top;
				TopTen->Controls->Add(label);
			}


			//SEARCHED NAMES SPECIFICALLY PANEL
			int labelHeight_Search = SearchedNamesPanel->Height / 10;

			// Add ten labels to the panel
			for (int i = 1; i <= 10; i++)
			{
				Label^ label = gcnew Label();
				label->Name = "search" + i;
				label->Text = "-";
				label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				label->AutoSize = false;
				label->Width = SearchedNamesPanel->Width;
				label->Height = labelHeight_Search;
				label->Top = (i - 1) * labelHeight_Search;
				SearchedNamesPanel->Controls->Add(label);
			}


			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Window()
		{
			if (components)
			{
				delete components;
			}
		}
	
	
	private: MapWrapper^ mapper;

	private: System::Windows::Forms::Label^ Title;


	private: System::Windows::Forms::TextBox^ NameInput;
	private: System::Windows::Forms::Label^ NameInputLabel;
	private: System::Windows::Forms::Label^ label1;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ year_from_TB;
	private: System::Windows::Forms::TextBox^ year_to_TB;


	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;



	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::CheckedListBox^ StateBox;

	private: System::Windows::Forms::ComboBox^ GenderBox;
	private: System::Windows::Forms::ComboBox^ SortTypeDropDown;
	private: System::Windows::Forms::Button^ SearchButton;

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ OutputLabl;

	private: System::Windows::Forms::Panel^ BottomTen;
	private: System::Windows::Forms::Panel^ TopTen;
private: System::Windows::Forms::Label^ label6;
private: System::Windows::Forms::Label^ label5;
private: System::Windows::Forms::Label^ label9;
private: System::Windows::Forms::Panel^ SearchedNamesPanel;
private: System::Windows::Forms::PictureBox^ pictureBox1;


private: System::Windows::Forms::PictureBox^ pictureBox2;
private: System::Windows::Forms::Label^ label11;
private: System::Windows::Forms::Label^ label8;
private: System::Windows::Forms::PictureBox^ pictureBox3;
private: System::Windows::Forms::Label^ label12;
private: System::Windows::Forms::Label^ label10;






	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;


	
	


	


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Window::typeid));
			this->Title = (gcnew System::Windows::Forms::Label());
			this->NameInput = (gcnew System::Windows::Forms::TextBox());
			this->NameInputLabel = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->year_from_TB = (gcnew System::Windows::Forms::TextBox());
			this->year_to_TB = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->StateBox = (gcnew System::Windows::Forms::CheckedListBox());
			this->GenderBox = (gcnew System::Windows::Forms::ComboBox());
			this->SortTypeDropDown = (gcnew System::Windows::Forms::ComboBox());
			this->SearchButton = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->SearchedNamesPanel = (gcnew System::Windows::Forms::Panel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->TopTen = (gcnew System::Windows::Forms::Panel());
			this->BottomTen = (gcnew System::Windows::Forms::Panel());
			this->OutputLabl = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// Title
			// 
			this->Title->BackColor = System::Drawing::Color::Orange;
			this->Title->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Title->Dock = System::Windows::Forms::DockStyle::Top;
			this->Title->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->Title->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Title->Location = System::Drawing::Point(0, 0);
			this->Title->Name = L"Title";
			this->Title->Size = System::Drawing::Size(1960, 79);
			this->Title->TabIndex = 0;
			this->Title->Text = L"NAME - A - GATOR";
			this->Title->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// NameInput
			// 
			this->NameInput->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NameInput->Location = System::Drawing::Point(62, 200);
			this->NameInput->Name = L"NameInput";
			this->NameInput->Size = System::Drawing::Size(374, 24);
			this->NameInput->TabIndex = 2;
			this->NameInput->Text = L"Separate Names by Spaces";
			// 
			// NameInputLabel
			// 
			this->NameInputLabel->AutoSize = true;
			this->NameInputLabel->BackColor = System::Drawing::Color::Orange;
			this->NameInputLabel->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NameInputLabel->Location = System::Drawing::Point(63, 163);
			this->NameInputLabel->Name = L"NameInputLabel";
			this->NameInputLabel->Size = System::Drawing::Size(132, 25);
			this->NameInputLabel->TabIndex = 3;
			this->NameInputLabel->Text = L"Name(s):";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Orange;
			this->label1->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(64, 263);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(117, 25);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Gender:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Orange;
			this->label2->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(63, 328);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(297, 25);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Year or Year Range:";
			// 
			// year_from_TB
			// 
			this->year_from_TB->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->year_from_TB->Location = System::Drawing::Point(62, 366);
			this->year_from_TB->Name = L"year_from_TB";
			this->year_from_TB->Size = System::Drawing::Size(152, 24);
			this->year_from_TB->TabIndex = 7;
			this->year_from_TB->Text = L"1910";
			// 
			// year_to_TB
			// 
			this->year_to_TB->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->year_to_TB->Location = System::Drawing::Point(284, 366);
			this->year_to_TB->Name = L"year_to_TB";
			this->year_to_TB->Size = System::Drawing::Size(152, 24);
			this->year_to_TB->TabIndex = 8;
			this->year_to_TB->Text = L"2021";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label3->Location = System::Drawing::Point(234, 362);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(31, 30);
			this->label3->TabIndex = 9;
			this->label3->Text = L"-";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Orange;
			this->label4->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(63, 735);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(192, 25);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Sorting Type";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::Orange;
			this->label7->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(63, 434);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(237, 25);
			this->label7->TabIndex = 14;
			this->label7->Text = L"State Selection";
			// 
			// StateBox
			// 
			this->StateBox->CheckOnClick = true;
			this->StateBox->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->StateBox->FormattingEnabled = true;
			this->StateBox->Location = System::Drawing::Point(63, 472);
			this->StateBox->Name = L"StateBox";
			this->StateBox->Size = System::Drawing::Size(368, 204);
			this->StateBox->TabIndex = 51;
			// 
			// GenderBox
			// 
			this->GenderBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->GenderBox->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->GenderBox->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->GenderBox->FormattingEnabled = true;
			this->GenderBox->Location = System::Drawing::Point(220, 262);
			this->GenderBox->Name = L"GenderBox";
			this->GenderBox->Size = System::Drawing::Size(216, 26);
			this->GenderBox->TabIndex = 16;
			// 
			// SortTypeDropDown
			// 
			this->SortTypeDropDown->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->SortTypeDropDown->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SortTypeDropDown->FormattingEnabled = true;
			this->SortTypeDropDown->Location = System::Drawing::Point(274, 732);
			this->SortTypeDropDown->Name = L"SortTypeDropDown";
			this->SortTypeDropDown->Size = System::Drawing::Size(156, 26);
			this->SortTypeDropDown->TabIndex = 17;
			// 
			// SearchButton
			// 
			this->SearchButton->BackColor = System::Drawing::Color::DarkGreen;
			this->SearchButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->SearchButton->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 36, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SearchButton->ForeColor = System::Drawing::Color::DarkOrange;
			this->SearchButton->Location = System::Drawing::Point(82, 802);
			this->SearchButton->Name = L"SearchButton";
			this->SearchButton->Size = System::Drawing::Size(322, 129);
			this->SearchButton->TabIndex = 52;
			this->SearchButton->Text = L"SEARCH";
			this->SearchButton->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->SearchButton->UseVisualStyleBackColor = false;
			this->SearchButton->Click += gcnew System::EventHandler(this, &Window::SearchButton_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::PaleGreen;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel1->Controls->Add(this->label9);
			this->panel1->Controls->Add(this->SearchedNamesPanel);
			this->panel1->Controls->Add(this->label6);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->TopTen);
			this->panel1->Controls->Add(this->BottomTen);
			this->panel1->Controls->Add(this->OutputLabl);
			this->panel1->Location = System::Drawing::Point(471, 254);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1182, 676);
			this->panel1->TabIndex = 54;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label9->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(774, 102);
			this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(306, 25);
			this->label9->TabIndex = 6;
			this->label9->Text = L"Searched Name Results";
			// 
			// SearchedNamesPanel
			// 
			this->SearchedNamesPanel->BackColor = System::Drawing::Color::Bisque;
			this->SearchedNamesPanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->SearchedNamesPanel->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SearchedNamesPanel->Location = System::Drawing::Point(728, 132);
			this->SearchedNamesPanel->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->SearchedNamesPanel->Name = L"SearchedNamesPanel";
			this->SearchedNamesPanel->Size = System::Drawing::Size(416, 510);
			this->SearchedNamesPanel->TabIndex = 4;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->label6->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(381, 102);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(292, 25);
			this->label6->TabIndex = 5;
			this->label6->Text = L"10 Most Common Names";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->label5->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(36, 102);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(292, 25);
			this->label5->TabIndex = 4;
			this->label5->Text = L"10 Most Unique Names";
			// 
			// TopTen
			// 
			this->TopTen->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->TopTen->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->TopTen->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TopTen->Location = System::Drawing::Point(387, 132);
			this->TopTen->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->TopTen->Name = L"TopTen";
			this->TopTen->Size = System::Drawing::Size(298, 510);
			this->TopTen->TabIndex = 3;
			// 
			// BottomTen
			// 
			this->BottomTen->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->BottomTen->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->BottomTen->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BottomTen->Location = System::Drawing::Point(42, 132);
			this->BottomTen->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->BottomTen->Name = L"BottomTen";
			this->BottomTen->Size = System::Drawing::Size(298, 510);
			this->BottomTen->TabIndex = 2;
			// 
			// OutputLabl
			// 
			this->OutputLabl->AutoSize = true;
			this->OutputLabl->BackColor = System::Drawing::Color::Bisque;
			this->OutputLabl->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->OutputLabl->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->OutputLabl->Location = System::Drawing::Point(42, 43);
			this->OutputLabl->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->OutputLabl->Name = L"OutputLabl";
			this->OutputLabl->Size = System::Drawing::Size(53, 32);
			this->OutputLabl->TabIndex = 0;
			this->OutputLabl->Text = L"--";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(1732, -9);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(228, 220);
			this->pictureBox1->TabIndex = 55;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.BackgroundImage")));
			this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox2->Location = System::Drawing::Point(-6, -9);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(228, 220);
			this->pictureBox2->TabIndex = 57;
			this->pictureBox2->TabStop = false;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::Orange;
			this->label11->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label11->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 22, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(849, 225);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(414, 48);
			this->label11->TabIndex = 58;
			this->label11->Text = L"SEARCH RESULTS";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label8
			// 
			this->label8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->label8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label8->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(346, 97);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(1245, 62);
			this->label8->TabIndex = 59;
			this->label8->Text = L"What is a name\'s uniquity\? We rank your search based off of real US Census data t"
				L"o calculate just how unique your name is.\r\n\r\n";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::PaleGreen;
			this->pictureBox3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.BackgroundImage")));
			this->pictureBox3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pictureBox3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox3->Location = System::Drawing::Point(1694, 269);
			this->pictureBox3->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(222, 472);
			this->pictureBox3->TabIndex = 63;
			this->pictureBox3->TabStop = false;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->BackColor = System::Drawing::Color::Orange;
			this->label12->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label12->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 22, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(1720, 229);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(162, 48);
			this->label12->TabIndex = 64;
			this->label12->Text = L"RANKS";
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label10
			// 
			this->label10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->label10->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label10->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 9, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(1710, 765);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(196, 168);
			this->label10->TabIndex = 65;
			this->label10->Text = L"Note that these percents are percentiles of total found names, not the uniquity %"
				L" itself.";
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Window
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->BackColor = System::Drawing::Color::DarkBlue;
			this->ClientSize = System::Drawing::Size(1920, 1018);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->SearchButton);
			this->Controls->Add(this->SortTypeDropDown);
			this->Controls->Add(this->GenderBox);
			this->Controls->Add(this->StateBox);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->year_to_TB);
			this->Controls->Add(this->year_from_TB);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->NameInputLabel);
			this->Controls->Add(this->NameInput);
			this->Controls->Add(this->Title);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"Window";
			this->Text = L"Name-A-Gator 4.0";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void SearchButton_Click(System::Object^ sender, System::EventArgs^ e) {

		//NAMES: get from text box and convert from system to std library string type
		String^ inputNames = NameInput->Text;
		std::string convertNames = msclr::interop::marshal_as<std::string>(inputNames);
		
		std::vector<std::string> userNames;
	
		std::stringstream ss(convertNames);
		std::string name;
		while (ss >> name) {
			userNames.push_back(name);
		}
		
		String^ selectedGender = GenderBox->SelectedItem->ToString();
		//std::string gender = marshal_as<std::string>(selectedGender);

		int fromYear = Int32::Parse(year_from_TB->Text);
		int toYear = Int32::Parse(year_to_TB->Text);

		//State Setter
		//Iterate through the checked items in the CheckedListBox
		//Declare a vector of strings to hold the checked state names
		std::vector<std::string> checkedStates;

		// Iterate through the checked items in the CheckedListBox
		for (int i = 0; i < StateBox->CheckedItems->Count; i++)
		{
			// Convert the checked item to a string and add it to the vector
			checkedStates.push_back(msclr::interop::marshal_as<std::string>(StateBox->CheckedItems[i]->ToString()));
		}

		if (checkedStates.size() == 0) {
			mapper->setAllStatesBool(true);
		}
		else {
			mapper->updateStateList(checkedStates);
		}

		mapper->setUniquitiesForAllNames(selectedGender, fromYear, toYear);

		OutputLabl->Text = "Loading Results!";

		//Bottom 10 (Most Unique for Search)
		std::vector<std::pair<std::string, float>>* uniquities = &mapper->getUniquityVector();

		auto begin_sort_time = std::chrono::system_clock::now();

		//SORTS
		if (SortTypeDropDown->SelectedItem->ToString() == "Merge Sort") {
			mapper->mergeSort(*uniquities, 0, uniquities->size() - 1);
		}
		else if (SortTypeDropDown->SelectedItem->ToString() == "Quick Sort") {
			mapper->quickSort(*uniquities, 0, uniquities->size() - 1);
		}
		else if (SortTypeDropDown->SelectedItem->ToString() == "Tim Sort") {
			mapper->timSort(*uniquities, uniquities->size());
		}
		else {
			mapper->combSort(*uniquities);
		}

		auto end_sort_time = std::chrono::system_clock::now();
		std::chrono::duration<double> sort_load_time = end_sort_time - begin_sort_time;

		double myDouble = std::chrono::duration_cast<std::chrono::duration<double>>(sort_load_time).count();
		System::String^ time = System::Convert::ToString(myDouble);

		OutputLabl->Text = "Search Completed in: " + time + " seconds";

		// Loop through the first ten pairs in the vector and set the Text property of each label
		for (int i = 0; i < 10 && i < uniquities->size(); i++) {
			// get the label control by name
			Label^ temp_label = dynamic_cast<Label^>(BottomTen->Controls->Find("uniquityLabel" + (i + 1), true)[0]);

			// set the text of the label to the unique name and its uniquity score
			temp_label->Text = gcnew String((std::to_string(i + 1) + ". " + uniquities->at(i).first + ": " + std::to_string(uniquities->at(i).second * 100) + "%").c_str());

		}
		int j = 0;
		int k = 1;
		// Loop through the last ten pairs in the vector and set the Text property of each label
		for (int i = uniquities->size()-1; i > uniquities->size() - 11; i--) {
			// get the label control by name
			Label^ temp_label = dynamic_cast<Label^>(TopTen->Controls->Find("commonLabel" + (j + 1), true)[0]);

			// set the text of the label to the unique name and its uniquity score
			temp_label->Text = gcnew String((std::to_string(k) + ". " + uniquities->at(i).first + ": " + std::to_string(uniquities->at(i).second * 100) + "%").c_str());
			j++;
			k++;
		}

		mapper->setRankingsVector(userNames);

		// Loop through searched names and set the Text property of each label
		for (int i = 0; i < 10; i++) {
			// get the label control by name
			Label^ temp_label = dynamic_cast<Label^>(SearchedNamesPanel->Controls->Find("search" + (i + 1), true)[0]);

			// set the text of the label to the unique name and its uniquity score

			temp_label->Text = "-";
		}

		std::vector<std::pair<std::string, float>>* name_ranks = &mapper->getRankingsVector();

		// Loop through searched names and set the Text property of each label
		for (int i = 0; i < userNames.size(); i++) {
			// get the label control by name
			Label^ temp_label = dynamic_cast<Label^>(SearchedNamesPanel->Controls->Find("search" + (i + 1), true)[0]);

			// set the text of the label to the unique name and its uniquity score

			temp_label->Text = gcnew String((userNames[i] + ": " + name_ranks->at(i).first + "  " + std::to_string(name_ranks->at(i).second * 100) + "%").c_str());
		}


		//Reset for next search
		mapper->clearUniquities();
		mapper->setAllStatesBool(false);
		mapper->clearRanksVec();
	}

private: System::Void panel2_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {

	for (int i = 0; i < 5; i++) {
		System::Drawing::Brush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(0, 100, 0, (i + 1) * 40));
		e->Graphics->FillRectangle(brush, 10, i * 40, 130, 30);
		System::Windows::Forms::TextBox^ textBox = gcnew System::Windows::Forms::TextBox();
		textBox->Location = System::Drawing::Point(10, 5);
		textBox->Size = System::Drawing::Size(110, 20);
		//panel2->Controls->Add(textBox);
	}
}
};
}
