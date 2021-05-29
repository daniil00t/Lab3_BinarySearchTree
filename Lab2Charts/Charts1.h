#pragma once
#include "GetData.h"

namespace Lab2Charts {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ Charts
	/// </summary>
	public ref class Charts : public System::Windows::Forms::Form
	{
	public:
		Charts(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Charts()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart_main;
	protected:
	private: System::Windows::Forms::Button^ button_init_chart;
	private: System::Windows::Forms::TextBox^ input_count;
	private: System::Windows::Forms::Button^ button_clear;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ select_method;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label_done_count;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label_average;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label_max;
	private: System::Windows::Forms::Label^ label_min;


	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

		

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->chart_main = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button_init_chart = (gcnew System::Windows::Forms::Button());
			this->input_count = (gcnew System::Windows::Forms::TextBox());
			this->button_clear = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->select_method = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label_done_count = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label_average = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label_max = (gcnew System::Windows::Forms::Label());
			this->label_min = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_main))->BeginInit();
			this->SuspendLayout();
			// 
			// chart_main
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart_main->ChartAreas->Add(chartArea1);
			legend1->LegendItemOrder = System::Windows::Forms::DataVisualization::Charting::LegendItemOrder::SameAsSeriesOrder;
			legend1->LegendStyle = System::Windows::Forms::DataVisualization::Charting::LegendStyle::Column;
			legend1->Name = L"Legend1";
			legend1->TableStyle = System::Windows::Forms::DataVisualization::Charting::LegendTableStyle::Wide;
			legend2->Name = L"Legend2";
			legend3->Name = L"Legend3";
			this->chart_main->Legends->Add(legend1);
			this->chart_main->Legends->Add(legend2);
			this->chart_main->Legends->Add(legend3);
			this->chart_main->Location = System::Drawing::Point(51, 35);
			this->chart_main->Name = L"chart_main";
			this->chart_main->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::Bright;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Legend = L"Legend1";
			series1->Name = L"Data";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Legend = L"Legend2";
			series2->Name = L"Average";
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->Legend = L"Legend3";
			series3->Name = L"Max";
			this->chart_main->Series->Add(series1);
			this->chart_main->Series->Add(series2);
			this->chart_main->Series->Add(series3);
			this->chart_main->Size = System::Drawing::Size(1171, 301);
			this->chart_main->TabIndex = 0;
			this->chart_main->Text = L"MainChart";
			this->chart_main->UseWaitCursor = true;
			this->chart_main->Click += gcnew System::EventHandler(this, &Charts::chart_main_Click);
			// 
			// button_init_chart
			// 
			this->button_init_chart->Location = System::Drawing::Point(1147, 374);
			this->button_init_chart->Name = L"button_init_chart";
			this->button_init_chart->Size = System::Drawing::Size(75, 23);
			this->button_init_chart->TabIndex = 1;
			this->button_init_chart->Text = L"Start chart";
			this->button_init_chart->UseVisualStyleBackColor = true;
			this->button_init_chart->Click += gcnew System::EventHandler(this, &Charts::button_init_chart_Click);
			// 
			// input_count
			// 
			this->input_count->Location = System::Drawing::Point(51, 375);
			this->input_count->Name = L"input_count";
			this->input_count->Size = System::Drawing::Size(100, 20);
			this->input_count->TabIndex = 2;
			// 
			// button_clear
			// 
			this->button_clear->Location = System::Drawing::Point(1049, 375);
			this->button_clear->Name = L"button_clear";
			this->button_clear->Size = System::Drawing::Size(75, 23);
			this->button_clear->TabIndex = 3;
			this->button_clear->Text = L"Clear";
			this->button_clear->UseVisualStyleBackColor = true;
			this->button_clear->Click += gcnew System::EventHandler(this, &Charts::button_clear_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(48, 350);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(84, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Count Elements:";
			// 
			// select_method
			// 
			this->select_method->FormattingEnabled = true;
			this->select_method->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Add_Test", L"Remove_Test", L"Find_Test",
					L"Balancing_Test"
			});
			this->select_method->Location = System::Drawing::Point(209, 374);
			this->select_method->Name = L"select_method";
			this->select_method->Size = System::Drawing::Size(121, 21);
			this->select_method->TabIndex = 5;
			this->select_method->Text = L"Method Test";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(51, 417);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(39, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Done: ";
			this->label2->Click += gcnew System::EventHandler(this, &Charts::label2_Click);
			// 
			// label_done_count
			// 
			this->label_done_count->AutoSize = true;
			this->label_done_count->Location = System::Drawing::Point(96, 417);
			this->label_done_count->Name = L"label_done_count";
			this->label_done_count->Size = System::Drawing::Size(13, 13);
			this->label_done_count->TabIndex = 7;
			this->label_done_count->Text = L"0";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(206, 417);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(50, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Average:";
			// 
			// label_average
			// 
			this->label_average->AutoSize = true;
			this->label_average->Location = System::Drawing::Point(273, 417);
			this->label_average->Name = L"label_average";
			this->label_average->Size = System::Drawing::Size(13, 13);
			this->label_average->TabIndex = 9;
			this->label_average->Text = L"0";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(206, 468);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(30, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Max:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(206, 443);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(27, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Min:";
			// 
			// label_max
			// 
			this->label_max->AutoSize = true;
			this->label_max->Location = System::Drawing::Point(273, 468);
			this->label_max->Name = L"label_max";
			this->label_max->Size = System::Drawing::Size(13, 13);
			this->label_max->TabIndex = 12;
			this->label_max->Text = L"0";
			// 
			// label_min
			// 
			this->label_min->AutoSize = true;
			this->label_min->Location = System::Drawing::Point(273, 443);
			this->label_min->Name = L"label_min";
			this->label_min->Size = System::Drawing::Size(13, 13);
			this->label_min->TabIndex = 13;
			this->label_min->Text = L"0";
			// 
			// Charts
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1299, 552);
			this->Controls->Add(this->label_min);
			this->Controls->Add(this->label_max);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label_average);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label_done_count);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->select_method);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button_clear);
			this->Controls->Add(this->input_count);
			this->Controls->Add(this->button_init_chart);
			this->Controls->Add(this->chart_main);
			this->Name = L"Charts";
			this->Text = L"Charts";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_main))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: vector<pair<int, float>> switcher(String^ method, int count) {
		if (method == "Add_Test") {
			return getTimePoints__Add(count);
		}
		else if(method == "Remove_Test"){
			return getTimePoints__Remove(count);
		}
		else if(method == "Find_Test"){
			return getTimePoints__Find(count);
		}
		else if(method == "Balancing_Test"){
			return getTimePoints__Balancing(count);
		}
		else {
			exit;
			return vector<pair<int, float>>();
		}
	}
	private: System::Void button_init_chart_Click(System::Object^ sender, System::EventArgs^ e) {
		int count = System::Convert::ToInt32(input_count->Text);
		String^ method = select_method->Text;
		const int HR = 100;
		int countIterators = count / HR;

		float AVERAGE = (float)0;
		float MAX = (float)0;
		float MIN = (float)100000;
		

		vector<pair<int, float>>* DATA = new vector<pair<int, float>>(count);
		for (size_t i = 0; i < countIterators; i++){
			*DATA = switcher(method, (i + 1) * HR);



			for (auto j = i * HR; j < (i + 1) * HR; j++) {
				this->chart_main->Series["Data"]->Points->AddXY((*DATA)[j].first, (*DATA)[j].second);
			}
			this->label_done_count->Text = "" + (i + 1) * HR + " elements";
			this->label_done_count->Update();

			float average = getAverage(DATA, &AVERAGE);
			float max = getMax(DATA, &MAX);

			this->label_average->Text = "" + average * 1000 + " ms";
			this->label_average->Update();

			this->chart_main->Series["Average"]->Points->Clear();


			this->chart_main->Series["Average"]->Points->AddXY(1, average);
			this->chart_main->Series["Average"]->Points->AddXY((i + 1) * HR, average);

			this->label_min->Text = "" + getMin(DATA, &MIN) * 1000 + " ms";
			this->label_min->Update();

			this->label_max->Text = "" + max * 1000  + " ms";
			this->label_max->Update();

			this->chart_main->Series["Max"]->Points->Clear();


			this->chart_main->Series["Max"]->Points->AddXY(1, max);
			this->chart_main->Series["Max"]->Points->AddXY((i + 1) * HR, max);

			this->chart_main->Update();

		}
		delete DATA;
		
	}
	private: System::Void button_clear_Click(System::Object^ sender, System::EventArgs^ e) {
		this->chart_main->Series["Data"]->Points->Clear();
		this->chart_main->Series["Average"]->Points->Clear();
		this->chart_main->Series["Max"]->Points->Clear();
		this->label_average->Text = "0";
		this->label_max->Text = "0";
		this->label_min->Text = "0";
		this->label_done_count->Text = "0";
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void chart_main_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
