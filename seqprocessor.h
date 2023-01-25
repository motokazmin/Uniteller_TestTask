#ifndef __PROCESSOR__
#define __PROCESSOR__

#include <algorithm>

template <typename T> class IdentifierSequence;

/*
    Базовый класс Логики добавления нового идентификатора
*/
class Processor
{
public:
    template<class T> int update(IdentifierSequence<T>& seq) {return 0;}
};

/*
    Класс Логики последовательного инкремента идентификатора группы.
    На примере требований от Uniteller отделная группа последовательности идентификаторов
    варьируется от A1 до Z9. Кроме того некоторые буквы нельзя использовать. Тогда максимальное
    колличество идентификаторов, которое можно записать в группу равняется m_maxGroupValue = 9*число_допустимых_букв.
    Логика IncProcessor построена на этом факте - в каждую группу мы пишем не более m_maxGroupValue раз, добавляя
    единицу при каждом обновлении. Как только мы в группу записали m_maxGroupValueраз, включается логика переноса 
    единицы на левые группы в последовательности.
*/
class IncProcessor : public Processor
{
    int m_maxGroupValue; // Вычисляется классом транслятора
    size_t m_currPos;    // Текущая группа для обновления

public:
    IncProcessor(int maxGroupValue) :
        m_maxGroupValue(maxGroupValue), m_currPos(0) {}

    // Метод добавления нового идентификатора
    template<class T> int update(IdentifierSequence<T>& seq)
    {
        if (std::all_of(seq.m_groups.begin(), seq.m_groups.end(),
            [&](int el){return el == m_maxGroupValue;}))
            return -1;

        return update_r(seq, m_currPos);
    }

private:
    // Логика переноса единицы
    template<class T> int update_r(IdentifierSequence<T>& seq, int pos)
    {
        if (seq.m_groups[pos] ==  m_maxGroupValue) {
            seq.m_groups[pos] = 1;
            if (pos == 0) {
                m_currPos++;
                seq.m_groups[m_currPos] = 1;
                return 0;
            } else {
                return update_r(seq, pos - 1);
            }
        }

        seq.m_groups[pos]++;
        return 0;
    }
};

#endif