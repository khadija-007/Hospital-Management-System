#pragma once

template <typename T>
class Storage
{
private:
    T data[100];
    int count;

public:
    Storage()
    {
        count = 0;
    }

    void add(const T& obj)
    {
        if (count < 100)
        {
            data[count] = obj;
            count++;
        }
    }

    void remove(int id)
    {
        int index = -1;

        for (int i = 0; i < count; i++)
        {
            if (data[i].getID() == id)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
            return;

        for (int i = index; i < count - 1; i++)
        {
            data[i] = data[i + 1];
        }

        count--;
    }

    T* findbyID(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (data[i].getID() == id)
            {
                return &data[i];
            }
        }
        return nullptr;
    }

    T& operator[](int index)
    {
        return data[index];
    }

    const T& operator[](int index) const
    {
        return data[index];
    }

    int getSize() const
    {
        return count;
    }
};