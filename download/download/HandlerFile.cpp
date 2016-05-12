#include "HandlerFile.h"
#include "Date.h"



HandlerFile::HandlerFile(string file)
{
	this->file = file;
	prop = Properties::newInstance(file);
}


HandlerFile::~HandlerFile()
{
	delete prop;
}
size_t fwrite_func(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	return fwrite(ptr, size, nmemb, stream);
}
void HandlerFile::download(string fileName) {
	Date* date1 = Date::newInstance();
	Date date2(prop->getValue("up_date"), Date::DB_FORMAT);
	long dif = (*date1 - date2);
	dif = dif / 86400;
	if (fileExists(fileName.c_str())) {
		if (dif == 0) return;
	}
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (!curl) return;
	//set_proxy_settings(curl);//my function




	//read settings file
	////////////////////////////////////
	string rest = prop->getValue("rest_query1")+to_string(dif)+prop->getValue("rest_query2");
	////////////////////////////////////

	//SSL Options
	//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER , 1);
	//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST , 1);
	//Provide CA Certs from http://curl.haxx.se/docs/caextract.html */
	//curl_easy_setopt(curl, CURLOPT_CAINFO, "G:/LaSpaceProg/SPACETRACK(LIBCURL)/Debug/ca-bundle.crt");
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);

	// Set up a couple initial paramaters that we will not need to mofiy later.
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/4.0");
	curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookie");

	// Visit the login page
	curl_easy_setopt(curl, CURLOPT_URL, "https://www.space-track.org/ajaxauth/login");
	char data[192];
	strcpy(data, "identity=");
	strcat(data, prop->getValue("user").c_str());
	strcat(data, "&password=");
	strcat(data, prop->getValue("password").c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
	printf("login: ");
	res = curl_easy_perform(curl);
	printf(": %s\n", curl_easy_strerror(res));


	curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
	FILE *data_file = fopen(fileName.c_str(), "wb");//fopen(files[i].c_str(), "wb");
	curl_easy_setopt(curl, CURLOPT_URL,rest.c_str());
	//cout << "Rest is = " << rest.c_str() << endl;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite_func);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, data_file);
	res = curl_easy_perform(curl);
	//if (res != CURLE_OK) fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	//else printf("rest query %2i: %s\n", i, curl_easy_strerror(res));
	fclose(data_file);

	curl_easy_cleanup(curl); //Always cleanup
							 //printf("End. Press any key...\n");
							 //getchar();
	changeDate(*date1, file);
};
void HandlerFile::changeDate(Date put, string file) {
	std::ofstream ofs(file.c_str());
	string user = "user: " + prop->getValue("user") + "\n";
	string pas = "password: " + prop->getValue("password") + "\n";
	string req1 = "rest_query1: " + prop->getValue("rest_query1") + "\n";
	string req2 = "rest_query2: " + prop->getValue("rest_query2") + "\n";
	string date = "up_date: " + put.getSTime();
 
	ofs << user;
	ofs << pas;
	ofs << req1;
	ofs << req2;
	ofs << date;

	ofs.close();
};

std::vector<std::string> &HandlerFile::split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}
std::vector<std::string> HandlerFile::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}
bool HandlerFile::fileExists(const char *fname){
	return access(fname, 0) != -1;
}