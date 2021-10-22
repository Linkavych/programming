/*
 * Inserting an image into a database (don't every really need to do this
 * but this is how.
 */
#include <sqlite3.h>
#include <stdio.h>

int main(int argc, char **argv) {

	FILE *fp = fopen("file.md", "rb");
	if (fp == NULL){
		fprintf(stderr, "Cannot open file\n");
		return 1;
	}

	fseek(fp, 0, SEEK_END);

	if (ferror(fp)) {
		fprintf(stderr, "fseek() failed\n");
		int r = fclose(fp);

		if (r == EOF) {
			fprintf(stderr, "Cannnot close file handler\n");
		}
		return 1;
	}

	int flen = ftell(fp);

	if (flen == -1) {
		perror("Error occurred\n");
		int r = fclose(fp);

		if (r == EOF) {
			fprintf(stderr, "Cannot close file handler\n");
		}
		return 1;
	}

	fseek(fp, 0, SEEK_SET);

	if (ferror(fp)) {
		fprintf(stderr, "fseek() failed\n");
		int r = fclose(fp);

		if (r == EOF) {
			fprintf(stderr, "Cannot close file handler\n");
		}
		return 1;
	}

	char data[flen+1];

	int size = fread(data, 1, flen, fp);

	if (ferror(fp)) {
		fprintf(stderr, "fread() failed\n");
		int r = fclose(fp);

		if (r == EOF) {
			fprintf(stderr, "Cannot close file handler\n");
		}
		return 1;
	}

	int r = fclose(fp);

	if (r == EOF) {
		fprintf(stderr, "Cannot close file handler\n");
	}

	sqlite3 *db;
	char *err_msg = 0;

	int rc = sqlite3_open("test.db", &db);

	if (rc != SQLITE_OK){
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);

		return 1;
	}

	sqlite3_stmt *pStmt;
	char *sql = "INSERT INTO Files VALUES(1, ?)";

	rc = sqlite3_prepare(db, sql, -1, &pStmt, 0);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
		return 1;
	}

	sqlite3_bind_blob(pStmt, 1, data, size, SQLITE_STATIC);

	rc = sqlite3_step(pStmt);

	if (rc != SQLITE_DONE){
		printf("Execution failed: %s\n", sqlite3_errmsg(db));
	}

	sqlite3_finalize(pStmt);
	sqlite3_close(db);

	return 0;
}
