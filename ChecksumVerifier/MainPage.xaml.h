//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace ChecksumVerifier
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		void FileBrowseClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void GenerateChecksums(Windows::Storage::StorageFile^ file);
		void md5CheckboxClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void sha1CheckboxClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void sha256Checkbox_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void sha512Checkbox_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		Platform::String^ getMD5Checksum(unsigned char* data, int dataLength);
		Platform::String^ getSHA1Checksum(unsigned char* data, int dataLength);
		Platform::String^ getSHA256Checksum(unsigned char* data, int dataLength);
		Platform::String^ getSHA512Checksum(unsigned char* data, int dataLength);
	};
}
