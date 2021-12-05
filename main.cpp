#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Point
{
    int x;
    int y;
};

void task1(const string &);
void task2(const string &);

int main() {
    string path;
    fstream fileStream;
    char confirmChar('m');

    cout << "AoC, day 5.\n";
    do {
        cout << "Type path to input file with puzzles:\n";
        cin >> path;

        fileStream.open(path);
        if(fileStream.is_open())
        {
            fileStream.close();
            cout << "File successfully opened!\n";
            cout << "First task data:\n";
            task1(path);

            cout << "Second task data:\n";
            task2(path);

            break;
        }
        else
        {
            fileStream.close();
            cout << "Wrong path to file. Not opened. Try again? y/n - ";
            cin >> confirmChar;
            if(confirmChar == 'y' || confirmChar == 'Y') confirmChar = 'm';
        }
    }while(confirmChar == 'm');
}

void task1(const string &path)
{
    vector<Point> dangerousPoints;
    fstream stream;

    stream.open(path);
    int dangerousPointsSize = 0;
    while(!stream.eof())
    {
        int idx = 0;
        string tempStr;
        getline(stream, tempStr);
        int k = 0;
        while(!tempStr.size() == 0)
        {
            string numStr; numStr.resize(2);
            if(tempStr[idx] == ',' || tempStr[idx] == ' ' || idx == tempStr.size() - 1)
            {
                if(idx == tempStr.size() - 1)
                    for(int copyIdx = 0; copyIdx <= idx; copyIdx++)
                        numStr[copyIdx] = tempStr[copyIdx];
                else
                    for(int copyIdx = 0; copyIdx < idx; copyIdx++)
                        numStr[copyIdx] = tempStr[copyIdx];

                k++;
                if(k % 2 == 1)
                {
                    dangerousPointsSize++;
                    dangerousPoints.resize(dangerousPointsSize);
                    dangerousPoints[dangerousPointsSize - 1].x = stoi(numStr);
                }
                else
                    dangerousPoints[dangerousPointsSize - 1].y = stoi(numStr);

                tempStr.erase(tempStr.begin(), tempStr.begin() + idx + 1);
                idx = 0;
            }
            else idx++;
            if(tempStr[0] == '-')
            {
                tempStr.erase(tempStr.begin(), tempStr.begin() + 3);
                idx = 0;
            }
        }
    }

    for(int idx = 0; idx < dangerousPoints.size(); idx += 2)
        if(dangerousPoints[idx].x != dangerousPoints[idx + 1].x && dangerousPoints[idx].y != dangerousPoints[idx + 1].y)
        {
            dangerousPoints.erase(dangerousPoints.begin() + idx);
            dangerousPoints.erase(dangerousPoints.begin() + idx);
            dangerousPointsSize -= 2;
            idx -= 2;
        }

    int maxY(0), maxX(0);
    for(int idx = 0; idx < dangerousPointsSize; idx++)
    {
        maxX = max(maxX, dangerousPoints[idx].x);
        maxY = max(maxY, dangerousPoints[idx].y);
    }

    vector<vector<int>> coordPlate;
    coordPlate.resize(maxX + 1);
    for(int idx = 0; idx < coordPlate.size(); idx++)
        coordPlate[idx].resize(maxY + 1);


    for(int idx = 0; idx < dangerousPointsSize; idx += 2)
    {
        if(dangerousPoints[idx].x == dangerousPoints[idx + 1].x)
        {
            int staticX = dangerousPoints[idx].x, finalY = dangerousPoints[idx + 1].y, currentY = dangerousPoints[idx].y;
            if(dangerousPoints[idx].y > finalY)
                while(currentY >= finalY)
                {
                    coordPlate[staticX][currentY]++;
                    currentY--;
                }
            else
                while(currentY <= finalY)
                {
                    coordPlate[staticX][currentY]++;
                    currentY++;
                }
        }
        else
        {
            int staticY = dangerousPoints[idx].y, finalX = dangerousPoints[idx + 1].x, currentX = dangerousPoints[idx].x;
            if(dangerousPoints[idx].x > finalX)
                while(currentX >= finalX)
                {
                    coordPlate[currentX][staticY]++;
                    currentX--;
                }
            else
                while(currentX <= finalX)
                {
                    coordPlate[currentX][staticY]++;
                    currentX++;
                }
        }
    }

    int dangerousPointsCount(0);
    for(int idxX = 0; idxX < coordPlate.size(); idxX++)
        for(int idxY = 0; idxY < coordPlate[idxX].size(); idxY++)
            if(coordPlate[idxX][idxY] >= 2) dangerousPointsCount++;

    cout << dangerousPointsCount << '\n';
}

void task2(const string &path)
{
    vector<Point> dangerousPoints;
    fstream stream;

    stream.open(path);
    int dangerousPointsSize = 0;
    while(!stream.eof())
    {
        int idx = 0;
        string tempStr;
        getline(stream, tempStr);
        int k = 0;
        while(!tempStr.size() == 0)
        {
            string numStr; numStr.resize(2);
            if(tempStr[idx] == ',' || tempStr[idx] == ' ' || idx == tempStr.size() - 1)
                {
                if(idx == tempStr.size() - 1)
                    for(int copyIdx = 0; copyIdx <= idx; copyIdx++)
                        numStr[copyIdx] = tempStr[copyIdx];
                else
                    for(int copyIdx = 0; copyIdx < idx; copyIdx++)
                        numStr[copyIdx] = tempStr[copyIdx];

                k++;
                if(k % 2 == 1)
                {
                    dangerousPointsSize++;
                    dangerousPoints.resize(dangerousPointsSize);
                    dangerousPoints[dangerousPointsSize - 1].x = stoi(numStr);
                }
                else
                    dangerousPoints[dangerousPointsSize - 1].y = stoi(numStr);

                tempStr.erase(tempStr.begin(), tempStr.begin() + idx + 1);
                idx = 0;
            }
            else idx++;
            if(tempStr[0] == '-')
            {
                tempStr.erase(tempStr.begin(), tempStr.begin() + 3);
                idx = 0;
            }
        }
    }

    int maxY(0), maxX(0);
    for(int idx = 0; idx < dangerousPointsSize; idx++)
    {
        maxX = max(maxX, dangerousPoints[idx].x);
        maxY = max(maxY, dangerousPoints[idx].y);
    }

    vector<vector<int>> coordPlate;
    coordPlate.resize(maxX + 1);
    for(int idx = 0; idx < coordPlate.size(); idx++)
        coordPlate[idx].resize(maxY + 1);


    while(dangerousPointsSize != 0)
    {
        if(dangerousPoints[0].x > dangerousPoints[1].x)
        {
            if(dangerousPoints[0].y > dangerousPoints[1].y)
            {
                int currentX = dangerousPoints[0].x, currentY = dangerousPoints[0].y;
                int finalX = dangerousPoints[1].x, finalY = dangerousPoints[1].y;

                while (currentX >= finalX && currentY >= finalY) {
                    coordPlate[currentX][currentY]++;
                    currentX--;
                    currentY--;
                }
            }
            else if(dangerousPoints[0].y < dangerousPoints[1].y)
            {
                int currentX = dangerousPoints[0].x, currentY = dangerousPoints[0].y;
                int finalX = dangerousPoints[1].x, finalY = dangerousPoints[1].y;

                while (currentX >= finalX && currentY <= finalY) {
                    coordPlate[currentX][currentY]++;
                    currentX--;
                    currentY++;
                }
            }
            else
            {
                int staticY = dangerousPoints[0].y;
                int currentX = dangerousPoints[0].x, finalX = dangerousPoints[1].x;

                while(currentX >= finalX)
                {
                    coordPlate[currentX][staticY]++;
                    currentX--;
                }
            }
        }
        else if(dangerousPoints[0].x < dangerousPoints[1].x)
        {
            if(dangerousPoints[0].y > dangerousPoints[1].y)
            {
                int currentX = dangerousPoints[0].x, currentY = dangerousPoints[0].y;
                int finalX = dangerousPoints[1].x, finalY = dangerousPoints[1].y;

                while (currentX <= finalX && currentY >= finalY) {
                    coordPlate[currentX][currentY]++;
                    currentX++;
                    currentY--;
                }
            }
            else if(dangerousPoints[0].y < dangerousPoints[1].y)
            {
                int currentX = dangerousPoints[0].x, currentY = dangerousPoints[0].y;
                int finalX = dangerousPoints[1].x, finalY = dangerousPoints[1].y;

                while (currentX <= finalX && currentY <= finalY) {
                    coordPlate[currentX][currentY]++;
                    currentX++;
                    currentY++;
                }
            }
            else
            {
                int staticY = dangerousPoints[0].y;
                int currentX = dangerousPoints[0].x, finalX = dangerousPoints[1].x;

                while(currentX <= finalX)
                {
                    coordPlate[currentX][staticY]++;
                    currentX++;
                }
            }
        }
        else
        {
            int staticX = dangerousPoints[0].x;
            int currentY = dangerousPoints[0].y, finalY = dangerousPoints[1].y;

            if(currentY > finalY)
                while(currentY >= finalY)
                {
                    coordPlate[staticX][currentY]++;
                    currentY--;
                }
            else
                while(currentY <= finalY)
                {
                    coordPlate[staticX][currentY]++;
                    currentY++;
                }
        }

        dangerousPoints.erase(dangerousPoints.begin(), dangerousPoints.begin() + 2);
        dangerousPointsSize -= 2;
    }

    int dangerousPointsCount(0);
    for(int idxX = 0; idxX < coordPlate.size(); idxX++)
        for(int idxY = 0; idxY < coordPlate[idxX].size(); idxY++)
            if(coordPlate[idxX][idxY] >= 2) dangerousPointsCount++;

    cout << dangerousPointsCount << '\n';
}