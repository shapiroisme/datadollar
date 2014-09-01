#include "economic.h"

economic::economic()
{
    DataLoaded = false;
    LoadError = false;
}


void economic::GetEconomicData()
{
    try{

        std::string host_("datadollar.info");
        std::string port_("80");
        std::string url_path("/GDPs.json");
        std::stringstream out_;
        std::vector<std::string> headers;

            using namespace boost::asio::ip;
            tcp::iostream request_stream;
            request_stream.connect(host_,port_);
            if(!request_stream){
                LoadError = true;
                DataLoaded = true;
                return;
            }
            request_stream << "GET " << url_path << " HTTP/1.0\r\n";
            request_stream << "Host: " << host_ << "\r\n";
            request_stream << "Accept: */*\r\n";
            request_stream << "Cache-Control: no-cache\r\n";
            request_stream << "Connection: close\r\n\r\n";
            request_stream.flush();
            std::string line1;
            std::getline(request_stream,line1);
            if (!request_stream)
            {
                LoadError = true;
                DataLoaded = true;
                return;
            }
            std::stringstream response_stream(line1);
            std::string http_version;
            response_stream >> http_version;
            unsigned int status_code;
            response_stream >> status_code;
            std::string status_message;
            std::getline(response_stream,status_message);
            if (!response_stream||http_version.substr(0,5)!="HTTP/")
            {
                LoadError = true;
                DataLoaded = true;
                return;
            }
            if (status_code!=200)
            {
                LoadError = true;
                DataLoaded = true;
                return;
            }
            std::string header;
            while (std::getline(request_stream, header) && header != "\r")
                headers.push_back(header);
            out_ << request_stream.rdbuf();

            QString data = QString::fromStdString(out_.str());

            Value value;
            read_string(data.toStdString(),value);

            if(value.type() == obj_type)
            {
                const Object& val = value.get_obj();
                value = find_value(val, "MaxMoney");
                if(!value.is_null())
                {
                    MAX_MONEY = value.get_int64();
                }
                else
                {
                    LoadError = true;
                }
            }
            else
            {
                LoadError = true;
            }
            DataLoaded = true;
        }catch(std::exception &e){
            LoadError = true;
            DataLoaded = true;
        }
}

// { "MaxMoney":12332434234 }
