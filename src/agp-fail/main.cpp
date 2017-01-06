#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <map>
#include "faidx.h"
#include "split.hpp"

int main(int argc, char *argv[]){

    bool any_error = false;

    std::vector<std::string> possible_errors;

    std::string correctVersion = "##agp-version 2.0";

    possible_errors.push_back("DUMMY: Problem opening AGP.  Stick to Exel.");
    possible_errors.push_back("DUMMY: How embarrassing your AGP has too few columns.");
    possible_errors.push_back("DUMMY: No or wrong version.");
    possible_errors.push_back("DUMMY: Try again.");

    std::vector<std::string> your_errors;

    if(argc != 3){
        std::cerr << "Usage: agp-fail <AGP.txt> <fasta.fa> " << std::endl << std::endl;
        std::cerr << "Required: AGP   <STRING> - An AGP v2.0 file." <<std::endl;
        std::cerr << "          FASTA <STRING> - The fasta that matches the AGP." <<std::endl;
        std::cerr << std::endl;
        std::cerr << "Details:  This program checks your fasta against your AGP and INSULTS you!" << std::endl;
        exit(1);
    }

    const char * fasta = argv[2];
    std::cerr << "INFO: fasta: " << fasta << std::endl;

    faidx_t * FA = fai_load(argv[2]);

    std::ifstream AGP;

    AGP.open(argv[1]);

    if(!AGP.is_open()){
        std::cerr << possible_errors[0] << std::endl;
        fai_destroy(FA);
        AGP.close();
        exit(1);
    }

    bool has_version = false;

    std::string line;

    while(getline (AGP,line)){
        if(line == correctVersion){
            has_version = true;
        }
        if(line[0] == '#'){
            continue;
        }
        std::vector<std::string> linedat = split(line, "\t");
        if(linedat.size() < 5){
            your_errors.push_back(possible_errors[1]);
            any_error = true;
        }
        if(linedat[4] == "N"){
            int len = 0;


            char * gapSeq = faidx_fetch_seq(FA,
                                         linedat[0].c_str(),
                                         atoi(linedat[1].c_str())-1,
                                         atoi(linedat[2].c_str())-1,
                                         &len);

            if(len < 0){
                std::cerr << "DUMMY: no fasta entry or range for: " << linedat[0] << ":" << linedat[1] << "-" << linedat[2] << std::endl;
                std::cerr << "       I see you know how to code in Pythong." << std::endl;
            }
            for(int i = 0; i < len; i++){
                if(gapSeq[i] != 'N'){
                    std::cerr << "DUMMY: only NNNs are allowed in gaps! : " <<  linedat[0] << ":" << linedat[1] << "-" << linedat[2] << " " << gapSeq[i] << " at " << i+1 <<std::endl;
                    std::cerr << "       rm -rf is always an option." << std::endl;
                    any_error = true;
                }
            }
            free(gapSeq);
        }
    }

    if(!has_version){
        your_errors.push_back(possible_errors[2]);
        any_error = true;
    }

    for(std::vector<std::string>::iterator it = your_errors.begin(); it != your_errors.end(); it++){
        std::cerr << *it << std::endl;
    }

    AGP.close();
    fai_destroy(FA);

    if(any_error) return 1;
    if(!any_error){
        std::cerr << "HOLY SHIT, NO ERRORS!" << std::endl;
        return 0;
    }
    return 0;
}
