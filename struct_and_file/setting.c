#include "setting.h"

//Hàm countDays để tính số ngày 
int countDays(int day, int month, int year) {
    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Tính số ngày trong các năm trước năm cho trước
    int totalDays = year * 365;

    // Thêm số ngày của các tháng trước tháng cho trước
    for (int i = 0; i < month - 1; i++) {
        totalDays += monthDays[i];
    }

    // Thêm số ngày từ đầu tháng đến ngày cho trước
    totalDays += day;

    // Thêm số ngày nhuận
    totalDays += year / 4 - year / 100 + year / 400;

    // Trừ đi số ngày nhuận nếu năm cho trước là năm nhuận và tháng nhỏ hơn 3
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) && month < 3) {
        totalDays--;
    }

    return totalDays;
}

void printDate_from_countDays(int totalDays) {
    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Xác định năm
    int year = 0; // Năm bắt đầu từ 1970, epoch time

    // Tính số ngày nhuận từ năm 1970 đến năm hiện tại
    while (totalDays >= 365) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            // Năm nhuận
            if (totalDays >= 366) {
                totalDays -= 366;
                (year)++;
            } else {
                break;
            }
        } else {
            // Năm không nhuận
            totalDays -= 365;
            (year)++;
        }
    }

    // Cập nhật số ngày của tháng 2 nếu là năm nhuận
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        monthDays[1] = 29;
    }

    // Xác định tháng và ngày trong tháng cho năm đó
    int month = 0;
    while (totalDays >= monthDays[month]) {
        totalDays -= monthDays[month];
        (month)++;
    }
    month += 1; // Tháng bắt đầu từ 1
    int day = totalDays + 1; // Ngày bắt đầu từ 1
       printf("%02d/%02d/%04d\n", day, month, year);
}

void reduceCurrentIndex(int *index) {
    (*index)--;
}

void increaseCurrentIndex(int *index) {
    (*index)++;
}