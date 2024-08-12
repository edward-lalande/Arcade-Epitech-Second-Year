/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** CreateMenu
*/

#ifndef CREATEMENU_HPP_
    #define CREATEMENU_HPP_

    #include <iostream>
    #include <vector>

    #include "JSON.hpp"

class Object {

    public:

        Object(

            double position[2],
            double type,
            double id

        ) {

            JSON::JSONArray __allPositions;
            JSON::JSON __posititon;

            __posititon._values["x"] = position[0];
            __posititon._values["y"] = position[1];

            __allPositions._values.push_back(__posititon);

            _json._values["id"] = id;
            _json._values["type"] = type;
            _json._values["position"] = __allPositions;

        };

        JSON::JSON _json;

};

class Image : public Object {

    public:

        Image(

            double position[2],
            double type,
            double id,
            std::string assets,
            std::string string,
            double rectangle[4]

        ): Object(position, type, id) {

            JSON::JSONArray __rectangle;

            __rectangle._values.push_back(rectangle[0]);
            __rectangle._values.push_back(rectangle[1]);
            __rectangle._values.push_back(rectangle[2]);
            __rectangle._values.push_back(rectangle[3]);

            _json._values["assets"] = assets;
            _json._values["string"] = string;
            _json._values["rectangle"] = __rectangle;

        };

};

class Text : public Object {

    public:

        Text(

                double position[2],
                double type,
                double id,
                std::string fontFamily,
                std::string content,
                double fontSize,
                double color[3],
                double value

        ): Object(position, type, id) {

                JSON::JSONArray __color;

                __color._values.push_back(color[0]);
                __color._values.push_back(color[1]);
                __color._values.push_back(color[2]);

                _json._values["fontFamily"] = fontFamily;
                _json._values["fontSize"] = fontSize;
                _json._values["content"] = content;
                _json._values["value"] = value;
                _json._values["fontColor"] = __color;

        }

};

class Shape : public Object {

    public:

        Shape(

            double position[2],
            double type,
            double id,
            double size[2],
            double fillColor[4],
            double outlineColor[4]

        ): Object(position, type, id) {

            JSON::JSONArray __size;
            JSON::JSONArray __fillColor;
            JSON::JSONArray __outlineColor;

            __size._values.push_back(size[0]);
            __size._values.push_back(size[1]);

            __fillColor._values.push_back(fillColor[0]);
            __fillColor._values.push_back(fillColor[1]);
            __fillColor._values.push_back(fillColor[2]);
            __fillColor._values.push_back(fillColor[3]);

            __outlineColor._values.push_back(outlineColor[0]);
            __outlineColor._values.push_back(outlineColor[1]);
            __outlineColor._values.push_back(outlineColor[2]);
            __outlineColor._values.push_back(outlineColor[3]);

            _json._values["size"] = __size;
            _json._values["fillColor"] = __fillColor;
            _json._values["outlineColor"] = __outlineColor;

        };

};

static const std::vector<Object> menuElements = {

    Image((double[2]){0.0, 0.0}, 0.0, 100.0, "Assets/background.jpg", "", (double[4]){0, 0, 1920, 1080}),
    Shape((double[2]){50.0, 50.0}, 2.0, 101.0, (double[2]){1820, 160}, (double[4]){0, 0, 0, 255}, (double[4]){255, 255, 255, 255}),
    Text((double[2]){420.0, 65.0}, 1.0, 104.0, "Assets/Fonts/ARCADE_I.ttf", "4RCAD3 P3T", 108, (double[3]){255, 255, 255}, -1),
    Shape((double[2]){50.0, 280.0}, 2.0, 102.0, (double[2]){370, 700}, (double[4]){0, 0, 0, 255}, (double[4]){255, 255, 255, 255}),
    Shape((double[2]){500.0, 280.0}, 2.0, 103.0, (double[2]){1370, 700}, (double[4]){0, 0, 0, 255}, (double[4]){255, 255, 255, 255}),

};

#endif /* !CREATEMENU_HPP_ */
