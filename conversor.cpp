#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

int testaNome (string NomeI, string NomeS, string P) {
    bool tester = false;
    size_t tname = NomeI.length();
    size_t tnames = NomeS.length();
    size_t prefix = P.length();
    if(tname < 5 || tnames < 5){
        cerr << "O nome do arquivo passado não é valido por não conter extensão.";
        return 1;
    }
    for (char caractere : NomeI) {
        if (caractere == '.') {
            tester = true;
        }
    }
    if(tester == false){
        cerr << "O nome do arquivo passado não é valido por não conter extensão.";
        return 1;
    }
    for (char caractere : NomeS) {
        if (caractere == '.') {
            tester = true;
        }
    }
    if(tester == false){
        cerr << "O nome do arquivo passado não é valido por não conter extensão.";
        return 1;
    }

    return 0;    
}
 
int main(int argc, char** argv) {
    // Verifica se foi fornecido o número correto de argumentos
    if (argc != 4) {
        cerr << "Uso: " << argv[0] << " <input_image> <output_image> <output_format>" << endl;
        cout << "n 1" << argv[1] << endl;
        cout << "n 2" << argv[2] << endl;
        cout << "n 3" << argv[3] << endl; 
        cout << "se faltou algum, deu erro!";
        return -1;
    }

    string inputDocument = argv[1];
    string outputDocument = argv[2];
    string outputFormat = argv[3];

    if(testaNome(inputDocument, outputDocument, outputFormat) == 1){
        return -1;
    }

    if (outputFormat == "jpg" || outputFormat == "png" || outputFormat == "tiff" || outputFormat == "bmp" || outputFormat == "webp" || outputFormat == "raw" || outputFormat == "hdr" || outputFormat == "gif") {
        // Carrega a imagem de entrada
        cv::Mat image = cv::imread(argv[1], cv::IMREAD_UNCHANGED);

        if (image.empty()) {
            cerr << "Erro ao carregar a imagem." << endl;
            return -1;
        }   
        cv::imwrite(argv[2], image);
        cout << "Conversão para " << outputFormat << " concluída com sucesso." << endl;
    } else if (outputFormat == "pgm") {
        // Carregando a imagem PGM
        cv::Mat image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

        if (image.empty()) {
            cerr << "Erro ao carregar a imagem." << endl;
            return -1;
        }

        // Salvando a imagem como P2 (ASCII)
        ofstream outfile(argv[2]);

        if (!outfile) {
            cerr << "Erro ao abrir o arquivo de saída." << endl;
            return -1;
        }

        outfile << "P2\n";
        outfile << "# Imagem convertida de " << argv[1] << "\n";
        outfile << image.cols << " " << image.rows << "\n";
        outfile << "255\n";  // Valor máximo de pixel

        for (int i = 0; i < image.rows; ++i) {
            for (int j = 0; j < image.cols; ++j) {
                outfile << static_cast<int>(image.at<uchar>(i, j)) << " ";
            }
            outfile << "\n";
        }

        cout << "Conversão concluída com sucesso. Imagem salva em " << argv[2] << endl;

    } else if ( outputFormat == "pdf" || outputFormat == "docx") {
        size_t posPonto = inputDocument.find_last_of(".");
        std::string novoNome = inputDocument.substr(0, posPonto) + "_copy" + inputDocument.substr(posPonto);
        string duplica = "cp " + inputDocument + " " + novoNome;
        int dup = system(duplica.c_str()); 
        string libreOfficeCommand = "libreoffice --headless --convert-to " + outputFormat + " " + inputDocument;
        int result = system(libreOfficeCommand.c_str());
        string mudaNome = "mv " + inputDocument + " " + outputDocument;

        // Verifica se o comando foi executado com sucesso
        if (result == 0) {
            int name = system(mudaNome.c_str());
            std::cout << "Conversão para " << outputFormat << " concluída com sucesso." << std::endl;
        } else {
            std::cerr << "Erro ao converter o documento." << std::endl;
            return -1;
        }

    } else if (outputFormat == "mp4") {
        string execyt = "yt-dlp -f 'bestvideo[ext=mp4]+bestaudio[ext=mp4]' -o " + outputDocument + " " + inputDocument;
        int execmp4 = system(execyt.c_str());
        if(execmp4 == 0){
            cout << "Download do video feito com sucesso! salvo com o nome: " << outputDocument << endl;
        }else{
            std::cerr << "Erro ao baixar o video." << std::endl;
            return -1;
        }
    }  else if (outputFormat == "mp3") {
        string execytmp3 = "yt-dlp -x --audio-format mp3 -o " + outputDocument + " " + inputDocument;
        int execmp3 = system(execytmp3.c_str());
        if(execmp3 == 0){
            cout << "Download do audio feito com sucesso! salvo com o nome: " << outputDocument << endl;
        }else{
            std::cerr << "Erro ao baixar o audio." << std::endl;
            return -1;
        }   
    }else if (outputFormat == "comprimir"){
        cv::VideoCapture capture(inputDocument);

        if (!capture.isOpened()) {
            std::cerr << "Erro ao abrir o vídeo de entrada." << std::endl;
            return -1;
        }

        // Configuração das propriedades do vídeo
        int frame_width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
        int frame_height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);

        // Cria o objeto VideoWriter para o vídeo de saída comprimido
        cv::VideoWriter compressedVideoWriter(outputDocument, cv::VideoWriter::fourcc('H', '2', '6', '4'), 30, cv::Size(frame_width, frame_height));
        if (!compressedVideoWriter.isOpened()) {
            std::cerr << "Erro ao criar o objeto VideoWriter." << std::endl;
            return -1;
        }

        // Processa e grava o vídeo
        while (true) {
            cv::Mat frame;
            capture >> frame;

            if (frame.empty())
                break;

            // Aplica suas operações de processamento aqui, se necessário

            // Grava o quadro no arquivo de vídeo comprimido
            compressedVideoWriter.write(frame);
        }

        // Libera os recursos
        capture.release();
        compressedVideoWriter.release();
    
    } else {
        cerr << "Formato de saída não suportado." << endl;
        return -1;
    }

    return 0;
}
