#pragma once
#include <vector>
#include <iostream>
#include <cstddef>

class Line{
	public:
		Line();
		Line(Line const & );
		Line(Line &&);
		Line & operator=(Line const & );
		Line & operator=(Line &&);
		Line(size_t size);
		~Line() = default;
		size_t size() const;
		float const & x(size_t it) const;
		float & x(size_t it);
		float const & y(size_t it) const;
		float & y(size_t it);
	private:
		std::vector<float> xx;
		std::vector<float> yy;
};

Line::Line(Line const & line):xx(line.xx),yy(line.yy){	
}
Line::Line(Line && line):xx(std::move(line.xx)),yy(std::move(line.yy)){
}
Line & Line:: operator=(Line const & line){
	xx = line.xx;
	yy = line.yy;
	return *this;
}
Line & Line::operator=(Line && line){
	xx = std::move(line.xx);
	yy = std::move(line.yy);
	return *this;
}
Line::Line(size_t size){
	for(size_t it=0; it<size; it++) xx.push_back(0);
	for(size_t it=0; it<size; it++) yy.push_back(0);	
}
size_t Line::size() const{
	return xx.size();
}
float const & Line::x(size_t it) const{
	return xx.at(it);
}
float & Line::x(size_t it){
	return xx.at(it);
}
float const & Line::y(size_t it) const{
	return yy.at(it);
}
float & Line::y(size_t it){
	return yy.at(it);
}

