/**
 * @file main.cpp
 *
 * @brief Main file for the SecureMac application
 *
 * @author Zarox28
 */

// ----- INCLUDES -----
#include "../libs/Logger/logger.cpp"

#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <chrono>
#include <thread>

// ----- NAMESPACES -----
using namespace std;
using namespace chrono;
using namespace Logger;

// ----- VARIABLES -----
bool motionDetected = false;
bool noticationSent = false;
bool isRecording    = false;
bool debugEnabled   = false;

pid_t ffmpegProcessID = -1;  // Process ID of the ffmpeg process

// ----- FUNCTIONS -----
// Starts recording webcam
void startRecording()
{
  auto      now = system_clock::to_time_t(system_clock::now());  // Get current time
  struct tm timeInfo;                                            // Time info
  char      buffer[80];                                          // Buffer for time string

  localtime_r(&now, &timeInfo);                                   // Get local time
  strftime(buffer, sizeof(buffer), "%d_%m_%Y-%H_%M", &timeInfo);  // Format time

  string directory = "video";

  // Create directory if it doesn't exist
  if (access(directory.c_str(), F_OK) == -1)
  {
    string createDirCommand = "mkdir -p " + directory;
    system(createDirCommand.c_str());
  }

  // Delete old video file if it exists
  if (access((directory + "/" + buffer + ".mp4").c_str(), F_OK) != -1)
  {
    string deleteFileCommand = "rm " + directory + "/" + buffer + ".mp4";
    system(deleteFileCommand.c_str());
  }

  string command = "ffmpeg -f avfoundation -framerate 30 -i \"0\" -vf \"format=yuv420p\" "
                 + directory + "/" + buffer + ".mp4 > /dev/null 2>&1 &";

  // Start recording
  FILE *ffmpegProcess = popen(command.c_str(), "r");
  if (ffmpegProcess)
  {
    fscanf(ffmpegProcess, "%d", &ffmpegProcessID);
    pclose(ffmpegProcess);
  }

  warn("Recording video...");

  info(("Video name: " + string(buffer) + ".mp4").c_str());      // Log video name
  system(("echo " + string(buffer) + ".mp4 | pbcopy").c_str());  // Copy video name

  isRecording = true;
}

// Locks the computer
void lockComputer()
{
  system("pmset displaysleepnow");
  info("Locking computer");
}

// Detects mouse motion by comparing the current mouse position with the last
bool detectMouseMotion()
{
  CGEventRef     event                = CGEventCreate(NULL);
  CGPoint        currentMousePosition = CGEventGetLocation(event);
  static CGPoint lastMousePosition    = currentMousePosition;

  // Compare the current mouse position with the last
  if (currentMousePosition.x != lastMousePosition.x || currentMousePosition.y != lastMousePosition.y)
  {
    lastMousePosition = currentMousePosition;

    return true;
  }

  return false;
}

// Detects keyboard events by checking the state of the alpha key
bool detectKeyboardEvent()
{
  CGEventRef event             = CGEventCreate(NULL);
  bool       isAlphaKeyPressed = CGEventGetFlags(event) & kCGEventFlagMaskAlphaShift;

  return isAlphaKeyPressed;
}

// Callback function for mouse events
CGEventRef mouseEventTapCallback(
  CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon
)
{
  if (type == kCGEventKeyDown || type == kCGEventKeyUp) return nullptr;

  if (type == kCGEventMouseMoved)
  {
    if (debugEnabled) debug("Mouse event detected");

    motionDetected = true;
  }

  return event;
}

// Callback function for keyboard events
CGEventRef keyboardEventTapCallback(
  CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon
)
{
  if (type == kCGEventMouseMoved) return nullptr;

  if (type == kCGEventKeyDown)
  {
    if (debugEnabled) debug("Keyboard event detected");

    motionDetected = true;
  }

  return event;
}

// Sets up the event tap
void setupEventTap(CGEventMask eventMask, CGEventTapCallBack callback)
{
  // Create event tap
  CFMachPortRef eventTap = CGEventTapCreate(
    kCGSessionEventTap,
    kCGHeadInsertEventTap,
    kCGEventTapOptionListenOnly,
    eventMask,
    callback,
    nullptr
  );

  if (! eventTap)
  {
    error("Error creating event tap.");
    exit(EXIT_FAILURE);
  }

  // Add event tap to run loop
  CFRunLoopSourceRef runLoopSource
    = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
  CGEventTapEnable(eventTap, true);
  CFRunLoopRun();
}

// Sets up the mouse event tap
void setupMouseEventTap()
{
  setupEventTap(
    1 << kCGEventMouseMoved, mouseEventTapCallback
  );  // Only listen for mouse move events
}

// Sets up the keyboard event tap
void setupKeyboardEventTap()
{
  // Listen for key down, key up and flags changed events
  setupEventTap(
    (1 << kCGEventKeyDown) | (1 << kCGEventKeyUp) | (1 << kCGEventFlagsChanged),
    keyboardEventTapCallback
  );
}

// ----- MAIN LOOP -----
int main(int argc, char *argv[])
{
  printf("\033]2;%s\007", "SecureMac");  // Set terminal title
  printf("\033[2J\033[H");               // Clear terminal

  info("Starting...");

  if (argc > 1 && string(argv[1]) == "debug") debugEnabled = true;  // Enable debug mode

  thread mouseThread(setupMouseEventTap);        // Start mouse event tap
  thread keyboardThread(setupKeyboardEventTap);  // Start keyboard event tap

  lockComputer();

  success("Started");

  while (true)
  {
    this_thread::sleep_for(seconds(1));

    if (motionDetected)
    {
      if (! noticationSent)
      {
        fatal("Motion detected");

        noticationSent = true;  // Prevents multiple notifications
      }

      if (! isRecording) startRecording();  // Start recording if not already recording

      motionDetected = false;
    }
  }

  mouseThread.join();     // Wait for mouse thread to finish
  keyboardThread.join();  // Wait for keyboard thread to finish

  return EXIT_SUCCESS;
}
