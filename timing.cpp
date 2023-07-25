    std::chrono::time_point<std::chrono::high_resolution_clock> argus_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> argus_end;

    std::chrono::time_point<std::chrono::high_resolution_clock> cuda_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> cuda_end;

    std::chrono::time_point<std::chrono::high_resolution_clock> river_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> river_end;

    std::chrono::time_point<std::chrono::high_resolution_clock> image_end;
    std::chrono::time_point<std::chrono::high_resolution_clock> image_start;


    //To measure image timing, insert this code at the beginning of ImageAcquisitionAndProcessing::returnImageBuffer before the call to image_frame->resetFrameIndex.  

    image_end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = image_end - image_start;
    std::cout << "Total Image Time: " << diff.count() * 1000 << std::endl;

    common_packages::Logging::LogText(
    vs::log_level_e::WARNING, LOGGING_CONTEXT, vs::String("Total Image Time: ") + vs::String(diff.count() * 1000) + vs::String(" ms"));

    image_start = std::chrono::high_resolution_clock::now();


    //To measure total argus timing:
    //Insert this code before the call to image_frame->resetFrameIndex in the function ImageAcquisitionAndProcessing::returnImageBuffer

    argus_start = std::chrono::high_resolution_clock::now();

    //Insert this code after the call to prcf_svcgh->enqueueToThread() in the function ImageAcquisitionAndProcessing::returnImageBuffer

    argus_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = argus_end - argus_start;
    std::cout << "Argus Time: " << diff.count() * 1000 << std::endl;

    common_packages::Logging::LogText(
    vs::log_level_e::WARNING, LOGGING_CONTEXT, vs::String("Argus Time: ") + vs::String(diff.count() * 1000) + vs::String(" ms"));

    //To measure total CUDA timing:  
    //Insert this code before the call to rivermaxSender.CopyImage in the function ImageAcquisitionAndProcessing::processRawCameraFrame
    cuda_start = std::chrono::high_resolution_clock::now();

    //Insert this code before the call to image_frame->resetFrameIndex in the function ImageAcquisitionAndProcessing::streamProcessedCameraFrame
    cuda_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = cuda_end - cuda_start;
    std::cout << "CUDA Time: " << diff.count() * 1000 << std::endl;

    common_packages::Logging::LogText(
    vs::log_level_e::WARNING, LOGGING_CONTEXT, vs::String("CUDA Time: ") + vs::String(diff.count() * 1000) + vs::String(" ms"));    

    //To measure total Rivermax timing:  
    //Insert this code before the call to rivermaxSender.CopyImage in the function ImageAcquisitionAndProcessing::streamProcessedCameraFrame
    river_start = std::chrono::high_resolution_clock::now();

    //Insert this code after the call to rib_svch->enqueueToThread(); in the function ImageAcquisitionAndProcessing::streamProcessedCameraFrame
    river_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = river_end - river_start;
    std::cout << "Rivermax Time: " << diff.count() * 1000 << std::endl;

    common_packages::Logging::LogText(
    vs::log_level_e::WARNING, LOGGING_CONTEXT, vs::String("Rivermax Time: ") + vs::String(diff.count() * 1000) + vs::String(" ms"));



