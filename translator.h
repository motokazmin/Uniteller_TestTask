using namespace std;

/*
    Базовый класс переводчика. Ничего не делает с внутренним представлением последовательности идентификаторов,
    оставляет как есть - удобно использовать для отладки.
*/
template<class T>
class Translator
{
public:
    virtual string Translate(T group)
    {
        return to_string(group);
    }
    int GetGroupCapacity()
    {
        return 3;
    }
};

/*
    Класс логики представления от Uniteller
*/
template<class T>
class UnitelTranslator : public Translator<T>
{
    int m_dictSize;

    const int m_numDigits = 9;
    const string m_dict = "ABCEHIKLNOPRSTUWXYZ";

public:
    UnitelTranslator()
    {
        m_dictSize = m_numDigits*m_dict.length();
    }

    virtual string Translate(T group)
    {
        T symbol = ((group - 1) / m_numDigits);
        return m_dict[symbol] + to_string((group - 1) - m_numDigits*symbol + 1);
    }

    int GetGroupCapacity()
    {
        return m_dictSize;
    }
};

 