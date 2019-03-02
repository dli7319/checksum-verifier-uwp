//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <openssl/md5.h>
#include <openssl/sha.h>

using namespace ChecksumVerifier;

using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::DataTransfer;

MainPage::MainPage()
{
	InitializeComponent();
}


void ChecksumVerifier::MainPage::FileBrowseClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FileOpenPicker^ openPicker = ref new FileOpenPicker();
	openPicker->FileTypeFilter->Append("*");
	create_task(openPicker->PickSingleFileAsync()).then([this](StorageFile^ file)
	{
		if (file)
		{
			filePathText->Text = file->Name;
			GenerateChecksums(file);
		}
	});

}

void ChecksumVerifier::MainPage::GenerateChecksums(StorageFile^ file)
{

	if (!file) {
		return;
	}

	if (true)
	{
		create_task(FileIO::ReadBufferAsync(file)).then([this, file](task<IBuffer^> task)
		{

			try
			{
				IBuffer^ buffer = task.get();
				DataReader^ dataReader = DataReader::FromBuffer(buffer);
				unsigned char* byteArr = new unsigned char[buffer->Length];
				dataReader->ReadBytes(ArrayReference<unsigned char>(byteArr, buffer->Length));

				if (md5Checkbox->IsChecked->Value) {
					md5Text->Text = getMD5Checksum(byteArr, buffer->Length);
				} else {
					md5Text->Text = "";
				}
				if (sha1Checkbox->IsChecked->Value) {
					sha1Text->Text = getSHA1Checksum(byteArr, buffer->Length);
				} else {
					sha1Text->Text = "";
				}
				if (sha256Checkbox->IsChecked->Value) {
					sha256Text->Text = getSHA256Checksum(byteArr, buffer->Length);
				} else {
					sha256Text->Text = "";
				}
				if (sha512Checkbox->IsChecked->Value) {
					sha512Text->Text = getSHA512Checksum(byteArr, buffer->Length);
				} else {
					sha512Text->Text = "";
				}

							   
				delete byteArr;
				delete dataReader;

			}
			catch (COMException^ ex)
			{

			}
		});
	}
}

String^ ChecksumVerifier::MainPage::getMD5Checksum(unsigned char *data, int dataLength)
{
	unsigned char result[MD5_DIGEST_LENGTH];
	MD5(data, dataLength, result);
	   
	char charBuffer[2 * MD5_DIGEST_LENGTH + 1];
	for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
		sprintf_s(charBuffer + 2 * i, 3, "%02x", result[i]);
	}
	std::string s_str(charBuffer);
	std::wstring wid_str(s_str.begin(), s_str.end());
	const wchar_t* w_char = wid_str.c_str();
	return(ref new String(w_char));
}

String^ ChecksumVerifier::MainPage::getSHA1Checksum(unsigned char *data, int dataLength)
{
	unsigned char result[SHA_DIGEST_LENGTH];
	SHA1(data, dataLength, result);

	char charBuffer[2 * SHA_DIGEST_LENGTH + 1];
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
		sprintf_s(charBuffer + 2 * i, 3, "%02x", result[i]);
	}
	std::string s_str(charBuffer);
	std::wstring wid_str(s_str.begin(), s_str.end());
	const wchar_t* w_char = wid_str.c_str();
	return(ref new String(w_char));
}

String^ ChecksumVerifier::MainPage::getSHA256Checksum(unsigned char *data, int dataLength)
{
	unsigned char result[SHA256_DIGEST_LENGTH];
	SHA256(data, dataLength, result);

	char charBuffer[2 * SHA256_DIGEST_LENGTH + 1];
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		sprintf_s(charBuffer + 2 * i, 3, "%02x", result[i]);
	}
	std::string s_str(charBuffer);
	std::wstring wid_str(s_str.begin(), s_str.end());
	const wchar_t* w_char = wid_str.c_str();
	return(ref new String(w_char));
}

String^ ChecksumVerifier::MainPage::getSHA512Checksum(unsigned char *data, int dataLength)
{
	unsigned char result[SHA512_DIGEST_LENGTH];
	SHA512(data, dataLength, result);

	char charBuffer[2 * SHA512_DIGEST_LENGTH + 1];
	for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
		sprintf_s(charBuffer + 2 * i, 3, "%02x", result[i]);
	}
	std::string s_str(charBuffer);
	std::wstring wid_str(s_str.begin(), s_str.end());
	const wchar_t* w_char = wid_str.c_str();
	return(ref new String(w_char));
}


void ChecksumVerifier::MainPage::md5CheckboxClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	
}


void ChecksumVerifier::MainPage::sha1CheckboxClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void ChecksumVerifier::MainPage::sha256Checkbox_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void ChecksumVerifier::MainPage::sha512Checkbox_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void ChecksumVerifier::MainPage::pasteButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	DataPackageView^ dataPackageView = DataTransfer::Clipboard::GetContent();
	if (dataPackageView->Contains(StandardDataFormats::Text))
	{
		create_task(dataPackageView->GetTextAsync()).then(
			[this](task<String^> textTask)
		{
			try
			{
				pasteChecksumInput->Text = textTask.get();
			}
			catch (Exception^ ex)
			{

			}
		});
	}
}
