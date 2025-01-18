#include "logic.h"

/*
 * @brief   Функция для заполнения матрицы ходом быка
 *
 * В переменных n_new и m_new будем хранить текущий индекс, когда встречается цифра, которая делится нацело
 * на количество строк, это означает, что это последния цифра в столбце. В таком случае, поменяем "путь" заполнения
 * массива на противоположный
 *
 * @param[out]   matrix[][M] указатель на матрицу
 * @param[in]   n   Количсество строк
 * @param[in]   m Количество столбцов
 *
 */
void fill_matrix(int matrix[][M], size_t n, size_t m)
{
    size_t f = 1;
    bool way = true;
    size_t n_new = n - 1, m_new = m - 1;
    while (f <= m * n)
    {
//        printf("%d %d\n", n_new, m_new);
        matrix[n_new][m_new] = f;
        if (f % n == 0)
        {
            way = !way;
            m_new--;
        }
        else
        {
            if (way)
            {
                n_new--;
            }
            else
            {
                n_new++;
            }
        }
        f++;
    }
}

