void getRentedCarData(ifstream &input, rentedCars rCars[])
{
    int i = 1;
    while (input >> rCars[i].realId >> rCars[i].rentedId >> rCars[i].sDate >> rCars[i].lDate >> rCars[i].day >> rCars[i].sMonth >> rCars[i].rent)
    {
        if (rCars[i].realId == (totalRentedCars - 1))
        {
            break;
        }
        i++;
    }
}
