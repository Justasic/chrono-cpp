
#include <iostream>
#include <string>

#include "src/parsers/en/ENCasualTimeParser.h"
#include "src/parsers/en/ENCasualDateParser.h"
#include "src/parsers/en/ENTimeLaterParser.hpp"
#include "src/parsers/en/ENMonthNameParser.hpp"
#include "src/parsers/en/ENDayOfTheWeekParser.hpp"
#include "src/parsers/en/ENTimeAgoFormatParser.hpp"
#include "src/parsers/en/ENDeadlineFormatParser.hpp"
#include "src/parsers/en/ENMonthNameMiddleEndianParser.hpp"

#include "src/refiners/OverlapRemovalRefiner.hpp"
#include "src/refiners/en/ENMergeDateRangeRefiner.hpp"


using namespace std;
using std::atoi;

void printUsage() {
    cout << "Usage: ./main [test string] [reference date] (last argument is optional) " << endl;
    cout << "If reference date is provided, format should be YYYY-MM-DD HH:MM:SS" << endl;
}

int main(int argc, char* argv[]) {
    if(argc < 2 or argc > 3) {
        printUsage();
        return 0;
    }
    Result results_pre, results_final;
    posix_time::ptime t;
    string str;

    Parser* tp  = new ENCasualTimeParser();
    Parser* dp  = new ENCasualDateParser();
    Parser* dfp = new ENDeadlineFormatParser();
    Parser* dow = new ENDayOfWeekParser();
    Parser* mme = new ENMonthNameMiddleEndianParser();
    Parser* tl  = new ENTimeLaterParser();
    Parser* mn  = new ENMonthNameParser();
    Parser* ta  = new ENTimeAgoFormatParser();

    // Refiner* ov  = new OverlapRemover();
    // Refiner* mdr = new ENMergeDateRange();

    list<Parser*>  parsers  {tp, dfp, dp, dow, mme, tl, mn, ta};
    // list<Refiner*> refiners {ov, mdr};

    str = argv[1];

    if (argc == 2){
        t = posix_time::second_clock::local_time();
    }

    if(argc == 3) {
        string refDate = argv[2];
        t = posix_time::time_from_string(refDate);
    }

    for(list<Parser*>::iterator it = parsers.begin(); it != parsers.end(); ++it) {
        Result p_result = (*it)->execute(str, t);
        results_pre.insert(results_pre.end(), p_result.begin(), p_result.end());
    }

    std::sort(results_pre.begin(), results_pre.end(),
            [&](parse::ParsedResult p1, parse::ParsedResult p2) {
                return p1.getIndex() < p2.getIndex();
    });

    /*for(list<Refiner*>::iterator it = refiners.begin(); it != refiners.end(); ++it) {
        results = (*it)->refine(results, str);
    }*/
    // results_final = ov->refine(mdr->refine(results_pre, str), str);

    if(results_pre.size() > 0)
        cout << "Date:\t"  << results_pre[0].toDate() << endl;
    else
        cout << "[???] -- Invalid date" << endl;

    return 0;
}