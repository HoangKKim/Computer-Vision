#include "function.h"

Mat objectDetection(Mat templateImg, Mat sceneImg) {
    Mat resImg = sceneImg.clone();

    // Convert images to grayscale
    Mat sceneGray, templateGray;
    cvtColor(sceneImg, sceneGray, COLOR_BGR2GRAY);
    cvtColor(templateImg, templateGray, COLOR_BGR2GRAY);

    // Initialize SIFT detector
    Ptr<Feature2D> sift = SIFT::create();
    vector<KeyPoint> keypoints_template, keypoints_scene;
    Mat descriptor_template, descriptor_scene;

    // Detect keypoints and compute descriptors
    sift->detectAndCompute(templateGray, Mat(), keypoints_template, descriptor_template);
    sift->detectAndCompute(sceneGray, Mat(), keypoints_scene, descriptor_scene);

    // Match descriptors using kNN (k-nearest neighbors)
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
    vector<vector<DMatch>> matches;
    matcher->knnMatch(descriptor_template, descriptor_scene, matches, 2);   // top 2 nearest neighbors for each descriptor
                                                                            // in the query set from the train set  

    // Filter matches based on distance ratio 
    vector<DMatch> goodMatches;
    float ratioThreshold = 0.75f;

    for (size_t i = 0; i < matches.size(); i++) {
        if (matches[i][0].distance < ratioThreshold * matches[i][1].distance) {
            goodMatches.push_back(matches[i][0]);
        }
    }

    // Extract matched keypoints
    vector<Point2f> matchedPoints1, matchedPoints2;
    for (const DMatch& match : goodMatches) {
        matchedPoints1.push_back(keypoints_template[match.queryIdx].pt);    // queryIdx use for template image
        matchedPoints2.push_back(keypoints_scene[match.trainIdx].pt);       // trainIdx use for scene image
    }

    // Find the homography transformation between two sets of points using RANSAX.
    float ransacReprojThreshold = 5.0f;
    Mat H = findHomography(matchedPoints1, matchedPoints2, RANSAC, ransacReprojThreshold);

    // Define corners of the template image
    vector<Point2f> templateCorners(4);
    templateCorners[0] = Point2f(0, 0);                                                 // top-left corner
    templateCorners[1] = Point2f((templateImg.cols - 1), 0);                            // top-right corner
    templateCorners[2] = Point2f((templateImg.cols - 1), (templateImg.rows - 1));       // bottom-right corner
    templateCorners[3] = Point2f(0, (templateImg.rows - 1));                            // bottom-left corner

    // Map template corners to scene image using homography
    vector<Point2f> sceneCorners(4);
    perspectiveTransform(templateCorners, sceneCorners, H);         // Mapping template corners to scene corners 
                                                                    // using the homography matrix H

    // Draw lines around the detected object
    for (int i = 0; i < 4; ++i) {
        line(resImg, sceneCorners[i], sceneCorners[(i + 1) % 4], Scalar(0, 255, 0), 2);
    }

    return resImg;
}