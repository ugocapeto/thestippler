double sample(
	// input
	const Mat &gray, 
	const float sample_r_min,
	const float sample_r_max,
	const Mat &bg_mask,
	const Mat &theEdgeMap,
	float (*sample_rad_func)(float x, float r_min, float r_max),
	// output
	Mat &out1,             // red points
	Mat &out2,             // binary
	vector<Point2i> &points
){
	clock_t t1 = clock();
	cvtColor(gray, out1, CV_GRAY2BGR);
	out2 = Mat::zeros(gray.size(), CV_8UC1);
	out2 = 255;
	points.clear();
	vector<vector<Point2i>> p_list(gray.rows);

	double radius;

	for(int y=0;y<gray.rows;y++){
		const uchar *p_row = gray.ptr<uchar>(y);
		const uchar *p_mask_row;
		if(bg_mask.data){
			p_mask_row = bg_mask.ptr<uchar>(y);
		}
		for(int x=0;x<gray.cols;x++){
			Point2i now = Point2i(x, y);
			radius = sample_rad_func((float)p_row[x]/255.0f, sample_r_min*2, sample_r_max*2) / 2;
			if(bg_mask.data){
				if(p_mask_row[x] == BLACK){
					radius = sample_r_max * 2;
				}
			}
			bool isIsolated = true;
			for(int i=y-radius;i<y+radius;i++){
				if(i < 0){
					i = 0;
				}else if(i >= p_list.size()){
					break;
				}
				vector<Point> *p = &p_list[i];
				if(x < gray.cols/2){
					for(int j=0;j<p->size();j++){
						if(dist((*p)[j], now) <= radius){
							isIsolated = false;
							break;
						}
						if((*p)[j].x > x + radius){
							break;
						}
					}
				}else{
					for(int j=p->size()-1;j>=0;j--){
						if(dist((*p)[j], now) <= radius){
							isIsolated = false;
							break;
						}
						if((*p)[j].x < x - radius){
							break;
						}
					}
				}
				if(!isIsolated) break;
			}
			if(isIsolated){
				p_list[y].push_back(now);
			}
		}
	}

	for(unsigned int i=0;i<p_list.size();i++){
		vector<Point> *p = &p_list[i];
		for(unsigned int j=0;j<p->size();j++){
			Point2i new_p((*p)[j]);
#if defined(SAMPLE_JIGGLE) && SAMPLE_JIGGLE==1
			int r1 = rand()%3-1;
			int r2 = rand()%3-1;

			if(new_p.x + r1 >= 0 && new_p.x + r1 < gray.cols){
				new_p.x += r1;
			}
			if(new_p.y + r2 >= 0 && new_p.y + r2 < gray.rows){
				new_p.y += r2;
			}
#endif
			points.push_back(new_p);
			circle(out1, new_p, 1, Scalar(0, 0, 255), -1);
			circle(out2, new_p, 0, 0);
		}
	}
	return (double)(clock() - t1) / CLOCKS_PER_SEC;
}
