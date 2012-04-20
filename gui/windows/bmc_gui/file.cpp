#include "stdafx.h"
#include "MainWindow.h"
namespace bmc_gui {

 System::Void MainWindow::onOpen(System::Object^  sender, System::EventArgs^  e) {
 
			openFileDialog1->Title = "Select a file";
			openFileDialog1->FileName = nullptr;
			openFileDialog1->InitialDirectory = "C:\\";
			openFileDialog1->DefaultExt = "bmc";
			openFileDialog1->Filter = "Braille Music (*.bmc)|*.txt|All (*.*)|*.*";
			openFileDialog1->CheckFileExists = true;
			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					System::IO::StreamReader ^ sr = gcnew System::IO::StreamReader(openFileDialog1->FileName);
					richTextBox1->Text = sr->ReadToEnd();
					sr->Close();
				}
		 }
 System::Void MainWindow::onQuit(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
 System::Void MainWindow::onSave(System::Object^  sender, System::EventArgs^  e) {
	
      saveFileDialog1->Filter = "Braille Music File|*.bmc";
      saveFileDialog1->Title = "Save a Braille Music File";
      saveFileDialog1->ShowDialog();
      // If the file name is not an empty string, open it for saving.
      if(saveFileDialog1->FileName != "")
      {
		 System::IO::StreamWriter ^ fs = gcnew System::IO::StreamWriter(saveFileDialog1->FileName);
         
		 fs->Write(richTextBox1->Text);
		 fs->Close();
		 this->Text = "BMC | " + saveFileDialog1->FileName;
		 }
	}
}