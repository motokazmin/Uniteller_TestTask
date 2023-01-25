#include <iostream>
#include "idproc.h"
#include "seqprocessor.h"

/*
    Решение построено на базе паттерна визитер, что позволяет снизить связанность кода и расширять
    функционал задавая новые правила построения идентификаторов. Три сущности лежат в основе предложенного
    решения: 
    
    1. Класс последовательности идентификаторов(IdentifierSequence) - чистые данные согласно
    требуемому формату последовательности идентификаторов.
    2. Класс логики добавления нового идентификатора (Processor) - логика добавления
    3. Класс Переводчик(Translator) - он отвечает за перевод внутреннего представления 
    идентификатора в читабельную форму.
    
    Можно легко создавать новые классы ЛОГИКИ ДОБАВЛЕНИЯ и ПЕРЕВОДЧИКОВ, комбинируя их, получая
    тем самым новые типы последовательностей.
*/

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cout << "Use idxs the_number_of_first_identifiers" << std::endl;
        return 0;
    }

    UnitelTranslator<int> tr;
    IdentifierSequence<int> is(4);
    IncProcessor seqp(tr.GetGroupCapacity());

    is.setProcessor(&seqp);
    is.setTranslator(&tr);

    for (int i = 0; i < std::stoi(argv[1]); i++) {
        if (is.update() == -1)
            break;
        std::cout << is.GetSequence() << std::endl;
    }

    return 0;
}