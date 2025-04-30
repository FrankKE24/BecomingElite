/*
 Flushes (writes) the contents of the buffer to the associated output stream without closing the stream.
 Use fflush() when you want to ensure that any buffered data is immediately written to the output, but you 
 still need to keep the stream open for further operations.
 
 
 FILE *file = fopen("example.txt", "w");
fprintf(file, "Hello, world!");
fflush(file);  // Ensures "Hello, world!" is written to the file immediately
fprintf(file, " More text.");
fclose(file);  // Closes the file when done*/