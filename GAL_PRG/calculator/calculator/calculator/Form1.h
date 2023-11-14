#pragma once
#include <cmath>

namespace calculator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btn_1;
	protected:
	private: System::Windows::Forms::Button^  btn_2;
	private: System::Windows::Forms::Button^  btn_3;
	private: System::Windows::Forms::Button^  btn_6;
	private: System::Windows::Forms::Button^  btn_5;
	private: System::Windows::Forms::Button^  btn_4;
	private: System::Windows::Forms::Button^  btn_9;
	private: System::Windows::Forms::Button^  btn_8;
	private: System::Windows::Forms::Button^  btn_7;

	private: System::Windows::Forms::Button^  btn_0;
	private: System::Windows::Forms::Button^  btn_clear;
	private: System::Windows::Forms::Button^  btn_add;
	private: System::Windows::Forms::Button^  btn_subtract;


	private: System::Windows::Forms::Button^  btn_result;
	private: System::Windows::Forms::Button^  btn_multiplication;
	private: System::Windows::Forms::Button^  btn_division;
	private: System::Windows::Forms::Button^  btn_comma;
	private: System::Windows::Forms::Button^ btn_percentage;
	private: System::Windows::Forms::Button^ btn_plusminus;
	private: System::Windows::Forms::Button^ btn_pow;
	private: System::Windows::Forms::Button^ btn_sqrt;
	private: System::Windows::Forms::Label^ resultBox;




	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->btn_1 = (gcnew System::Windows::Forms::Button());
			this->btn_2 = (gcnew System::Windows::Forms::Button());
			this->btn_3 = (gcnew System::Windows::Forms::Button());
			this->btn_6 = (gcnew System::Windows::Forms::Button());
			this->btn_5 = (gcnew System::Windows::Forms::Button());
			this->btn_4 = (gcnew System::Windows::Forms::Button());
			this->btn_9 = (gcnew System::Windows::Forms::Button());
			this->btn_8 = (gcnew System::Windows::Forms::Button());
			this->btn_7 = (gcnew System::Windows::Forms::Button());
			this->btn_0 = (gcnew System::Windows::Forms::Button());
			this->btn_clear = (gcnew System::Windows::Forms::Button());
			this->btn_add = (gcnew System::Windows::Forms::Button());
			this->btn_subtract = (gcnew System::Windows::Forms::Button());
			this->btn_result = (gcnew System::Windows::Forms::Button());
			this->btn_multiplication = (gcnew System::Windows::Forms::Button());
			this->btn_division = (gcnew System::Windows::Forms::Button());
			this->btn_comma = (gcnew System::Windows::Forms::Button());
			this->btn_percentage = (gcnew System::Windows::Forms::Button());
			this->btn_plusminus = (gcnew System::Windows::Forms::Button());
			this->btn_pow = (gcnew System::Windows::Forms::Button());
			this->btn_sqrt = (gcnew System::Windows::Forms::Button());
			this->resultBox = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// btn_1
			// 
			this->btn_1->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_1->Location = System::Drawing::Point(118, 422);
			this->btn_1->Margin = System::Windows::Forms::Padding(1);
			this->btn_1->Name = L"btn_1";
			this->btn_1->Size = System::Drawing::Size(75, 75);
			this->btn_1->TabIndex = 0;
			this->btn_1->Text = L"1";
			this->btn_1->UseVisualStyleBackColor = true;
			this->btn_1->Click += gcnew System::EventHandler(this, &Form1::btn_1_Click);
			// 
			// btn_2
			// 
			this->btn_2->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_2->Location = System::Drawing::Point(207, 422);
			this->btn_2->Margin = System::Windows::Forms::Padding(1);
			this->btn_2->Name = L"btn_2";
			this->btn_2->Size = System::Drawing::Size(75, 75);
			this->btn_2->TabIndex = 1;
			this->btn_2->Text = L"2";
			this->btn_2->UseVisualStyleBackColor = true;
			this->btn_2->Click += gcnew System::EventHandler(this, &Form1::btn_2_Click);
			// 
			// btn_3
			// 
			this->btn_3->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_3->Location = System::Drawing::Point(297, 422);
			this->btn_3->Margin = System::Windows::Forms::Padding(1);
			this->btn_3->Name = L"btn_3";
			this->btn_3->Size = System::Drawing::Size(75, 75);
			this->btn_3->TabIndex = 2;
			this->btn_3->Text = L"3";
			this->btn_3->UseVisualStyleBackColor = true;
			this->btn_3->Click += gcnew System::EventHandler(this, &Form1::btn_3_Click);
			// 
			// btn_6
			// 
			this->btn_6->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_6->Location = System::Drawing::Point(297, 329);
			this->btn_6->Margin = System::Windows::Forms::Padding(1);
			this->btn_6->Name = L"btn_6";
			this->btn_6->Size = System::Drawing::Size(75, 75);
			this->btn_6->TabIndex = 5;
			this->btn_6->Text = L"6";
			this->btn_6->UseVisualStyleBackColor = true;
			this->btn_6->UseWaitCursor = true;
			this->btn_6->Click += gcnew System::EventHandler(this, &Form1::btn_6_Click);
			// 
			// btn_5
			// 
			this->btn_5->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_5->Location = System::Drawing::Point(207, 329);
			this->btn_5->Margin = System::Windows::Forms::Padding(1);
			this->btn_5->Name = L"btn_5";
			this->btn_5->Size = System::Drawing::Size(75, 75);
			this->btn_5->TabIndex = 4;
			this->btn_5->Text = L"5";
			this->btn_5->UseVisualStyleBackColor = true;
			this->btn_5->Click += gcnew System::EventHandler(this, &Form1::btn_5_Click);
			// 
			// btn_4
			// 
			this->btn_4->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_4->Location = System::Drawing::Point(118, 329);
			this->btn_4->Margin = System::Windows::Forms::Padding(1);
			this->btn_4->Name = L"btn_4";
			this->btn_4->Size = System::Drawing::Size(75, 75);
			this->btn_4->TabIndex = 3;
			this->btn_4->Text = L"4";
			this->btn_4->UseVisualStyleBackColor = true;
			this->btn_4->Click += gcnew System::EventHandler(this, &Form1::btn_4_Click);
			// 
			// btn_9
			// 
			this->btn_9->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_9->Location = System::Drawing::Point(297, 239);
			this->btn_9->Margin = System::Windows::Forms::Padding(1);
			this->btn_9->Name = L"btn_9";
			this->btn_9->Size = System::Drawing::Size(75, 75);
			this->btn_9->TabIndex = 8;
			this->btn_9->Text = L"9";
			this->btn_9->UseVisualStyleBackColor = true;
			this->btn_9->Click += gcnew System::EventHandler(this, &Form1::btn_9_Click);
			// 
			// btn_8
			// 
			this->btn_8->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_8->Location = System::Drawing::Point(207, 239);
			this->btn_8->Margin = System::Windows::Forms::Padding(1);
			this->btn_8->Name = L"btn_8";
			this->btn_8->Size = System::Drawing::Size(75, 75);
			this->btn_8->TabIndex = 7;
			this->btn_8->Text = L"8";
			this->btn_8->UseVisualStyleBackColor = true;
			this->btn_8->Click += gcnew System::EventHandler(this, &Form1::btn_8_Click);
			// 
			// btn_7
			// 
			this->btn_7->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_7->Location = System::Drawing::Point(118, 239);
			this->btn_7->Margin = System::Windows::Forms::Padding(1);
			this->btn_7->Name = L"btn_7";
			this->btn_7->Size = System::Drawing::Size(75, 75);
			this->btn_7->TabIndex = 6;
			this->btn_7->Text = L"7";
			this->btn_7->UseVisualStyleBackColor = true;
			this->btn_7->Click += gcnew System::EventHandler(this, &Form1::btn_7_Click);
			// 
			// btn_0
			// 
			this->btn_0->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_0->Location = System::Drawing::Point(207, 508);
			this->btn_0->Margin = System::Windows::Forms::Padding(1);
			this->btn_0->Name = L"btn_0";
			this->btn_0->Size = System::Drawing::Size(75, 75);
			this->btn_0->TabIndex = 10;
			this->btn_0->Text = L"0";
			this->btn_0->UseVisualStyleBackColor = true;
			this->btn_0->Click += gcnew System::EventHandler(this, &Form1::btn_0_Click);
			// 
			// btn_clear
			// 
			this->btn_clear->BackColor = System::Drawing::Color::White;
			this->btn_clear->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->btn_clear->FlatAppearance->BorderColor = System::Drawing::Color::Red;
			this->btn_clear->FlatAppearance->BorderSize = 0;
			this->btn_clear->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_clear->Location = System::Drawing::Point(118, 150);
			this->btn_clear->Margin = System::Windows::Forms::Padding(0);
			this->btn_clear->Name = L"btn_clear";
			this->btn_clear->Size = System::Drawing::Size(75, 75);
			this->btn_clear->TabIndex = 11;
			this->btn_clear->Text = L"C";
			this->btn_clear->UseVisualStyleBackColor = false;
			this->btn_clear->Click += gcnew System::EventHandler(this, &Form1::btn_clear_Click);
			// 
			// btn_add
			// 
			this->btn_add->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_add->Location = System::Drawing::Point(389, 422);
			this->btn_add->Margin = System::Windows::Forms::Padding(1);
			this->btn_add->Name = L"btn_add";
			this->btn_add->Size = System::Drawing::Size(75, 75);
			this->btn_add->TabIndex = 12;
			this->btn_add->Text = L"+";
			this->btn_add->UseVisualStyleBackColor = true;
			this->btn_add->Click += gcnew System::EventHandler(this, &Form1::btn_add_Click);
			// 
			// btn_subtract
			// 
			this->btn_subtract->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_subtract->Location = System::Drawing::Point(389, 329);
			this->btn_subtract->Margin = System::Windows::Forms::Padding(1);
			this->btn_subtract->Name = L"btn_subtract";
			this->btn_subtract->Size = System::Drawing::Size(75, 75);
			this->btn_subtract->TabIndex = 13;
			this->btn_subtract->Text = L"-";
			this->btn_subtract->UseVisualStyleBackColor = true;
			this->btn_subtract->Click += gcnew System::EventHandler(this, &Form1::btn_subtract_Click);
			// 
			// btn_result
			// 
			this->btn_result->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_result->Location = System::Drawing::Point(389, 508);
			this->btn_result->Margin = System::Windows::Forms::Padding(1);
			this->btn_result->Name = L"btn_result";
			this->btn_result->Size = System::Drawing::Size(75, 75);
			this->btn_result->TabIndex = 14;
			this->btn_result->Text = L"=";
			this->btn_result->UseVisualStyleBackColor = true;
			this->btn_result->Click += gcnew System::EventHandler(this, &Form1::btn_result_Click);
			// 
			// btn_multiplication
			// 
			this->btn_multiplication->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_multiplication->Location = System::Drawing::Point(389, 239);
			this->btn_multiplication->Margin = System::Windows::Forms::Padding(1);
			this->btn_multiplication->Name = L"btn_multiplication";
			this->btn_multiplication->Size = System::Drawing::Size(75, 75);
			this->btn_multiplication->TabIndex = 15;
			this->btn_multiplication->Text = L"x";
			this->btn_multiplication->UseVisualStyleBackColor = true;
			this->btn_multiplication->Click += gcnew System::EventHandler(this, &Form1::btn_multiplication_Click);
			// 
			// btn_division
			// 
			this->btn_division->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_division->Location = System::Drawing::Point(389, 150);
			this->btn_division->Margin = System::Windows::Forms::Padding(1);
			this->btn_division->Name = L"btn_division";
			this->btn_division->Size = System::Drawing::Size(75, 75);
			this->btn_division->TabIndex = 16;
			this->btn_division->Text = L"/";
			this->btn_division->UseVisualStyleBackColor = true;
			this->btn_division->Click += gcnew System::EventHandler(this, &Form1::btn_division_Click);
			// 
			// btn_comma
			// 
			this->btn_comma->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_comma->Location = System::Drawing::Point(297, 508);
			this->btn_comma->Margin = System::Windows::Forms::Padding(1);
			this->btn_comma->Name = L"btn_comma";
			this->btn_comma->Size = System::Drawing::Size(75, 75);
			this->btn_comma->TabIndex = 17;
			this->btn_comma->Text = L",";
			this->btn_comma->UseVisualStyleBackColor = true;
			this->btn_comma->Click += gcnew System::EventHandler(this, &Form1::btn_comma_Click);
			// 
			// btn_percentage
			// 
			this->btn_percentage->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_percentage->Location = System::Drawing::Point(297, 150);
			this->btn_percentage->Margin = System::Windows::Forms::Padding(1);
			this->btn_percentage->Name = L"btn_percentage";
			this->btn_percentage->Size = System::Drawing::Size(75, 75);
			this->btn_percentage->TabIndex = 18;
			this->btn_percentage->Text = L"%";
			this->btn_percentage->UseVisualStyleBackColor = true;
			this->btn_percentage->Click += gcnew System::EventHandler(this, &Form1::btn_percentage_Click);
			// 
			// btn_plusminus
			// 
			this->btn_plusminus->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_plusminus->Location = System::Drawing::Point(207, 150);
			this->btn_plusminus->Margin = System::Windows::Forms::Padding(1);
			this->btn_plusminus->Name = L"btn_plusminus";
			this->btn_plusminus->Size = System::Drawing::Size(75, 75);
			this->btn_plusminus->TabIndex = 19;
			this->btn_plusminus->Text = L"+/-";
			this->btn_plusminus->UseVisualStyleBackColor = true;
			this->btn_plusminus->Click += gcnew System::EventHandler(this, &Form1::btn_plusminus_Click);
			// 
			// btn_pow
			// 
			this->btn_pow->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_pow->Location = System::Drawing::Point(28, 150);
			this->btn_pow->Margin = System::Windows::Forms::Padding(1);
			this->btn_pow->Name = L"btn_pow";
			this->btn_pow->Size = System::Drawing::Size(75, 75);
			this->btn_pow->TabIndex = 20;
			this->btn_pow->Text = L" x²";
			this->btn_pow->UseVisualStyleBackColor = true;
			this->btn_pow->Click += gcnew System::EventHandler(this, &Form1::btn_pow_Click);
			// 
			// btn_sqrt
			// 
			this->btn_sqrt->Font = (gcnew System::Drawing::Font(L"Arial", 25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_sqrt->Location = System::Drawing::Point(28, 239);
			this->btn_sqrt->Margin = System::Windows::Forms::Padding(1);
			this->btn_sqrt->Name = L"btn_sqrt";
			this->btn_sqrt->Size = System::Drawing::Size(75, 75);
			this->btn_sqrt->TabIndex = 21;
			this->btn_sqrt->Text = L"√x";
			this->btn_sqrt->UseVisualStyleBackColor = true;
			this->btn_sqrt->Click += gcnew System::EventHandler(this, &Form1::btn_sqrt_Click);
			// 
			// resultBox
			// 
			this->resultBox->AutoSize = true;
			this->resultBox->BackColor = System::Drawing::Color::Black;
			this->resultBox->Font = (gcnew System::Drawing::Font(L"Arial", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->resultBox->ForeColor = System::Drawing::Color::White;
			this->resultBox->Location = System::Drawing::Point(29, 24);
			this->resultBox->MinimumSize = System::Drawing::Size(435, 100);
			this->resultBox->Name = L"resultBox";
			this->resultBox->Size = System::Drawing::Size(435, 100);
			this->resultBox->TabIndex = 22;
			this->resultBox->Text = L"0";
			this->resultBox->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// Form1
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(484, 611);
			this->Controls->Add(this->resultBox);
			this->Controls->Add(this->btn_sqrt);
			this->Controls->Add(this->btn_pow);
			this->Controls->Add(this->btn_plusminus);
			this->Controls->Add(this->btn_percentage);
			this->Controls->Add(this->btn_comma);
			this->Controls->Add(this->btn_division);
			this->Controls->Add(this->btn_multiplication);
			this->Controls->Add(this->btn_result);
			this->Controls->Add(this->btn_subtract);
			this->Controls->Add(this->btn_add);
			this->Controls->Add(this->btn_clear);
			this->Controls->Add(this->btn_0);
			this->Controls->Add(this->btn_9);
			this->Controls->Add(this->btn_8);
			this->Controls->Add(this->btn_7);
			this->Controls->Add(this->btn_6);
			this->Controls->Add(this->btn_5);
			this->Controls->Add(this->btn_4);
			this->Controls->Add(this->btn_3);
			this->Controls->Add(this->btn_2);
			this->Controls->Add(this->btn_1);
			this->KeyPreview = true;
			this->MaximumSize = System::Drawing::Size(500, 650);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(500, 650);
			this->Name = L"Form1";
			this->Padding = System::Windows::Forms::Padding(1);
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"Calculator";
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::Form1_KeyPress);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		int numOfCalcs = 0;
		int currentOperation = 0;
		double num_1 = 0;
		double num_2 = 0;
		bool error = false;
		bool clear = false;
		bool comma = false;

		/*
			OPERATIONS
			1 = +
			2 = -
			3 = /
			4 = *
			5 = pow
			6 = sqrt
		*/

		private: System::Void btn_1_Click(System::Object^  sender, System::EventArgs^  e) {
			addNum("1");
		}
		private: System::Void btn_2_Click(System::Object^  sender, System::EventArgs^  e) {
			addNum("2");
		}
		private: System::Void btn_3_Click(System::Object^  sender, System::EventArgs^  e) {
			addNum("3");
		}
		private: System::Void btn_4_Click(System::Object^  sender, System::EventArgs^  e) {
			addNum("4");
		}
		private: System::Void btn_5_Click(System::Object^  sender, System::EventArgs^  e) {
			addNum("5");
		}
		private: System::Void btn_6_Click(System::Object^  sender, System::EventArgs^  e) {
			addNum("6");
		}
		private: System::Void btn_7_Click(System::Object^  sender, System::EventArgs^  e) {
			addNum("7");
		}
		private: System::Void btn_8_Click(System::Object^  sender, System::EventArgs^  e) {
			addNum("8");
		}
		private: System::Void btn_9_Click(System::Object^  sender, System::EventArgs^  e) {
			addNum("9");
		}
		private: System::Void btn_0_Click(System::Object^  sender, System::EventArgs^  e) {
			addNum("0");
		}
		private: System::Void btn_clear_Click(System::Object^  sender, System::EventArgs^  e) {
			clearResultBox();
		}
		private: System::Void btn_division_Click(System::Object^  sender, System::EventArgs^  e) {
			if (!error) {
				if (numOfCalcs > 0) {
					num_2 = System::Convert::ToDouble(resultBox->Text);
					calculate(num_1, num_2, currentOperation);
					numOfCalcs++;
					currentOperation = 3;
					num_1 = System::Convert::ToDouble(resultBox->Text);
					clear = true;
					numOfCalcs++;
					return;
				}
				currentOperation = 3;
				num_1 = System::Convert::ToDouble(resultBox->Text);
				clear = true;
				numOfCalcs++;
			}
		}
		private: System::Void btn_multiplication_Click(System::Object^  sender, System::EventArgs^  e) {
			if (!error) {

				if (numOfCalcs > 0) {
					num_2 = System::Convert::ToDouble(resultBox->Text);
					calculate(num_1, num_2, currentOperation);
					numOfCalcs++;
					currentOperation = 4;
					num_1 = System::Convert::ToDouble(resultBox->Text);
					clear = true;
					numOfCalcs++;
					return;
				}
				currentOperation = 4;
				num_1 = System::Convert::ToDouble(resultBox->Text);
				clear = true;
				numOfCalcs++;
			}
		}
		private: System::Void btn_add_Click(System::Object^  sender, System::EventArgs^  e) {
			if (!error) {

				if (numOfCalcs > 0) {
					num_2 = System::Convert::ToDouble(resultBox->Text);
					calculate(num_1, num_2, currentOperation);
					numOfCalcs++;
					currentOperation = 1;
					num_1 = System::Convert::ToDouble(resultBox->Text);
					clear = true;
					numOfCalcs++;
					return;
				}
				currentOperation = 1;
				num_1 = System::Convert::ToDouble(resultBox->Text);
				clear = true;
				numOfCalcs++;
			}
		}
		private: System::Void btn_subtract_Click(System::Object^  sender, System::EventArgs^  e) {
			if (!error) {

				if (numOfCalcs > 0) {
					num_2 = System::Convert::ToDouble(resultBox->Text);
					calculate(num_1, num_2, currentOperation);
					numOfCalcs++;
					currentOperation = 2;
					num_1 = System::Convert::ToDouble(resultBox->Text);
					clear = true;
					numOfCalcs++;
					return;
				}
				currentOperation = 2;
				num_1 = System::Convert::ToDouble(resultBox->Text);
				clear = true;
				numOfCalcs++;
			}
		}
		private: System::Void btn_percentage_Click(System::Object^ sender, System::EventArgs^ e) {
			if (!error) {
				if (numOfCalcs > 0) {
					num_2 = System::Convert::ToDouble(resultBox->Text);
					calculate(num_1, num_2, currentOperation);
				}
				if (!error || System::Convert::ToDouble(resultBox->Text) != 0) {
					double num = System::Convert::ToDouble(resultBox->Text);
					double result = num / 100;
					String^ resultString = System::Convert::ToString(result);
					resultBox->Text = resultString;
				}
			}
		}
		private: System::Void btn_plusminus_Click(System::Object^ sender, System::EventArgs^ e) {
			if (!error) {
				String^ currentText = resultBox->Text;
				if (currentText == "0" || currentText == "-0") {
					return;
				}
				if (currentText->StartsWith("-")) {
					currentText = currentText->Substring(1);
					resultBox->Text = currentText;
					return;
				}
				currentText = currentText->Insert(0, "-");
				resultBox->Text = currentText;
			}
		}
		private: System::Void btn_pow_Click(System::Object^ sender, System::EventArgs^ e) {
			if (!error) {
				if (numOfCalcs > 0) {
					num_2 = System::Convert::ToDouble(resultBox->Text);
					calculate(num_1, num_2, currentOperation);
				}
				if (!error || System::Convert::ToDouble(resultBox->Text) != 0) {
					double num = System::Convert::ToDouble(resultBox->Text);
					double result = pow(num, 2);
					String^ resultString = System::Convert::ToString(result);
					resultBox->Text = resultString;
				}
			}
		}
		private: System::Void btn_sqrt_Click(System::Object^ sender, System::EventArgs^ e) {
			if (!error) {
				if (numOfCalcs > 0) {
					num_2 = System::Convert::ToDouble(resultBox->Text);
					calculate(num_1, num_2, currentOperation);
				}
				if (!error || System::Convert::ToDouble(resultBox->Text) != 0) {
					double num = System::Convert::ToDouble(resultBox->Text);
					double result = sqrt(num);
					String^ resultString = System::Convert::ToString(result);
					resultBox->Text = resultString;
				}
			}
		}
		private: System::Void btn_result_Click(System::Object^  sender, System::EventArgs^  e) {
			if (numOfCalcs > 0) {
				num_2 = System::Convert::ToDouble(resultBox->Text);
				calculate(num_1, num_2, currentOperation);
			}
		}
		private: System::Void btn_comma_Click(System::Object^  sender, System::EventArgs^  e) {
			String ^currentText = resultBox->Text;
			if (currentText == "0" || error || comma) {
				return;
			}
			else {
				resultBox->Text += ",";
				comma = true;
			}
		}
		private: System::Void clearResultBox() {
			resultBox->Text = "0";
			error = false;
		}
		private: System::Void addNum(String ^num) {
			if (error) {
				resultBox->Text = "0";
				error = false;
				return;
			}
			if (clear) {
				clearResultBox();
				clear = false;
			}
			String ^currentText = resultBox->Text;
			double x = System::Convert::ToDouble(currentText);
			int numInt = System::Convert::ToInt32(num);
		
			if (numInt == 0) {
				if (x != 0) {
					resultBox->Text += num;
				}
			}else {
				if (x == 0) {
					resultBox->Text = "";
				}

				resultBox->Text += num;
			}
		}
		private: System::Void removeNum() {
			if (error) {
				resultBox->Text = "0";
				error = false;
				return;
			}
			if (clear) {
				clearResultBox();
				clear = false;
				return;
			}
			String^ currentText = resultBox->Text;
			if (currentText != "0") {
				currentText = currentText->Substring(0, currentText->Length - 1);
				resultBox->Text = currentText;
			}		
			if (currentText == "") {
				resultBox->Text = "0";
			}
		}
		private: System::Void calculate(double num1, double num2, int e) {
			clearResultBox();
			double result;
			String ^result_string;
			switch (e) {
			case 1:
				result = num1 + num2;
				result_string = System::Convert::ToString(result);
				resultBox->Text = result_string;
				break;
			case 2:
				result = num1 - num2;
				result_string = System::Convert::ToString(result);
				resultBox->Text = result_string;
				break;
			case 3:
				if (num2 == 0) {
					resultBox->Text = "Error";
					error = true;
					num_1 = 0;
					num_2 = 0;
					currentOperation = 0;
					numOfCalcs = 0;
					return;
				}
				result = num1 / num2;
				result_string = System::Convert::ToString(result);
				resultBox->Text = result_string;
				break;
			case 4:
				result = num1 * num2;
				result_string = System::Convert::ToString(result);
				resultBox->Text = result_string;
				break;
			}

			num_1 = 0;
			num_2 = 0;
			currentOperation = 0;
			numOfCalcs = 0;
		}

		// --------------------------
		// KEYBOARD INTERACTIONS
		// --------------------------

		private: System::Void Form1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
			String^ z = e->KeyChar.ToString();
			if (e->KeyChar == 8) {
				removeNum();
				return;
			}


			if (z == "1" || z == "2" || z == "3" || z == "4" || z == "5" || z == "6" || z == "7" || z == "8" || z == "9") {
				addNum(z);
			}
		}
	};
}
