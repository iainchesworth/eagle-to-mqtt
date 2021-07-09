#include "versions/versions_git.h"

bool GitMetadata::Populated() 
{
    return GIT_RETRIEVED_STATE;
}

bool GitMetadata::AnyUncommittedChanges() 
{
    return GIT_IS_DIRTY;
}

std::string GitMetadata::AuthorName() 
{
    return GIT_AUTHOR_NAME;
}

std::string GitMetadata::AuthorEmail() 
{
    return GIT_AUTHOR_EMAIL;
}

std::string GitMetadata::CommitSHA1() 
{
    return GIT_HEAD_SHA1;
}

std::string GitMetadata::CommitDate() 
{
    return GIT_COMMIT_DATE_ISO8601;
}

std::string GitMetadata::CommitSubject() 
{
    return GIT_COMMIT_SUBJECT;
}

std::string GitMetadata::CommitBody() 
{
    return GIT_COMMIT_BODY;
}

std::string GitMetadata::Describe() 
{
    return GIT_DESCRIBE;
}
