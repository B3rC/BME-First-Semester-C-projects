#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846

int main(void) {

    // Constants needed for rendering
    const int minuteTickStartDistance = 230;
    const int minuteTickEndDistance = 250;
    const int center = 256;
    const int hourHandLength = 130;
    const int minuteHandLength = 210;
    const int secondHandLength = 220;

    int hour, minute, second;

    printf("Enter the time between 0:00:00 and 23:59:59 (hour minute second, separated by spaces): \n");
    scanf("%d %d %d", &hour, &minute, &second);

    // Check if the user has entered a valid time
    while(hour > 23 || hour < 0 || minute > 59 || minute < 0 || second > 59 || second < 0) {
        printf("Invalid time format, please enter again: \n");
        scanf("%d %d %d", &hour, &minute, &second);
    }
    printf("The SVG will display the following time: %d hours %d minutes %d seconds \n", hour, minute, second);

    // Calculate the angles between the hands
    int secondAngle = (second * 6);
    int minuteAngle = (minute * 6);
    int hourAngle = (hour * 30);

    // Convert angles to radians (subtract 90 degrees for correct coordinate system positioning)
    double secondHandAngleRad = (secondAngle - 90) * (PI / 180.0);
    double minuteHandAngleRad = (minuteAngle + (secondAngle / 60) - 90) * (PI / 180.0); // Includes second hand position in calculation
    double hourHandAngleRad = (hourAngle + (minuteAngle / 12) - 90) * (PI / 180.0);

    // Calculate the coordinates for the SVG rendering of the hands
    int secondHandX2 = center + cos(secondHandAngleRad) * secondHandLength;
    int secondHandY2 = center + sin(secondHandAngleRad) * secondHandLength;

    int minuteHandX2 = center + cos(minuteHandAngleRad) * minuteHandLength;
    int minuteHandY2 = center + sin(minuteHandAngleRad) * minuteHandLength;

    int hourHandX2 = center + cos(hourHandAngleRad) * hourHandLength;
    int hourHandY2 = center + sin(hourHandAngleRad) * hourHandLength;

    // Basic SVG declarations to be written to the file
    const char* svgStart = "<svg width=\"512\" height=\"512\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">";
    const char* svgEnd = "</svg>";
    const char* clockCircle = "<circle cx=\"256\" cy=\"256\" r=\"251\" stroke=\"black\" fill=\"#d8f1ff\" stroke-width=\"5\" />";

    FILE* fp;
    fp = fopen("clock.svg", "w");

    // Write SVG file starting here
    fprintf(fp, "%s\n%s\n", svgStart, clockCircle);

    // Create minute ticks, with special emphasis on hour marks
    int startAngle = 0;

    for (int i = 0; i < 60; i++) {
        double angleInRadians = startAngle * (PI / 180.0);
        startAngle += 6;

        int x1 = 256 + cos(angleInRadians) * minuteTickStartDistance;  // Starting coordinates of minute tick
        int y1 = 256 + sin(angleInRadians) * minuteTickStartDistance;
        int x2 = 256 + cos(angleInRadians) * minuteTickEndDistance;  // Ending coordinates of minute tick
        int y2 = 256 + sin(angleInRadians) * minuteTickEndDistance;

        if(i % 5 == 0) {
            fprintf(fp,
                "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-width=\"8\" />\n",
                x1, y1, x2, y2);
        }
        else {
            fprintf(fp,
                "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-width=\"2\" />\n",
                x1, y1, x2, y2);
        }
    }

    // Draw the hour hand with the calculated coordinates
    fprintf(fp, "<line x1=\"256\" y1=\"256\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-width=\"9\" />\n", hourHandX2, hourHandY2);

    // Draw the minute hand with the calculated coordinates
    fprintf(fp, "<line x1=\"256\" y1=\"256\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-width=\"5\" />\n", minuteHandX2, minuteHandY2);

    // Draw the second hand with the calculated coordinates
    fprintf(fp, "<line x1=\"256\" y1=\"256\" x2=\"%d\" y2=\"%d\" stroke=\"red\" stroke-width=\"2\" />\n", secondHandX2, secondHandY2);

    // Draw a small circle at the center for design purposes
    fprintf(fp, "<circle cx=\"256\" cy=\"256\" r=\"5\" stroke=\"black\" fill=\"black\" stroke-width=\"5\" />\n");

    // End of SVG
    fprintf(fp, "%s\n", svgEnd);

    // Close the file
    fclose(fp);

    return 0;
}
