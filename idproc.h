#ifndef __IDPROC__
#define __IDPROC__

#include <vector>
#include <shared_mutex>
#include "seqprocessor.h"
#include "translator.h"

using namespace std;

/*
    Класс последовательности идентификаторов. Отвечает за хранение текущей последовательности.
*/
template<class T>
class IdentifierSequence
{
private:
    const size_t m_numGroups;     // Число групп в последовательности
    IncProcessor *m_processor;    // Визитер, логика обновления последовательности.
    Translator<T>* m_translator;  // Переводчик
    vector<T> m_groups;           // Сами группы
    mutable shared_mutex m_mutex;
public:
    IdentifierSequence(size_t numGroups) :
        m_numGroups(numGroups), m_processor(NULL) {
            m_groups.resize(numGroups);
            std::fill(begin(m_groups), end(m_groups), T());
    }

    // Метод получения текущей последовательности идентификаторов.
    string GetSequence() const {
        string identifier;
        shared_lock lock(m_mutex);

        for (auto &group : m_groups)
        {
            if (group != T())
                identifier += m_translator->Translate(group) + "-";
        }
        if (identifier[identifier.length() - 1] == '-')
            identifier.pop_back();

        return identifier;
    }

    void setProcessor(IncProcessor* processor) {
        m_processor = processor;
    }

    void setTranslator(Translator<T>* translator) {
        m_translator = translator;
    }

    // Метод, делегирующий визитеру процедуру обновления последовательности.
    int update()
    {
        unique_lock lock(m_mutex);
        return m_processor->update<T>(*this);
    }

    friend IncProcessor;
};

#endif